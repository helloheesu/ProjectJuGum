#include "NNConfig.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "NNInputSystem.h"
#include "NNCircle.h"
#include "NNSpriteAtlas.h"
#include "NetManager.h"
#include "Satellite.h"

CMaincharacter::CMaincharacter(void) : m_bHit(false), m_SatelliteIndex(0)
{
	m_Texture =  NNSpriteAtlas::Create(L"Sprite/warrior2_0.png");
	m_Texture->SetImageHeight(50.f);
	m_Texture->SetImageWidth(50.f);
	m_Texture->SetPosition(0.f, 0.f);
	AddChild( m_Texture );

	SetHitRadius(CHAR_HIT_RADIUS);
	m_Circle = NNCircle::Create(GetHitRadius());
	m_Circle->SetPosition(0.f, 0.f);
	m_Circle->SetColor(255.f, 0.f, 0.f);
	AddChild( m_Circle );

	m_Cost = 0;
	m_Stage = FIRST_STAGE_CHAR;

	m_bHit = false;
}

CMaincharacter::~CMaincharacter(void)
{
}

void CMaincharacter::Render()
{
	NNObject::Render();
}

//**************************************************************
//                         Update
//**************************************************************

//�׽�Ʈ�� �Լ�
void CMaincharacter::Update( float dTime, CMaincharacter* enemy, CMainMap* map )
{
	UpdateShotDirection(enemy);
	UpdateShotPoint();
	UpdateSatellite(dTime, enemy);

	m_Texture->SetRotation(GetShotDirection());

	UpdateMotion(dTime, NNInputSystem::GetInstance()->GetSkillKeyInput(), NNInputSystem::GetInstance()->GetDirectionKeyInput());
	SkillCasting(dTime, enemy, map, NNInputSystem::GetInstance()->GetSkillKeyInput());
}

void CMaincharacter::Update(float dTime, CMaincharacter* enemy, CMainMap* map, int framenum)
{
	//�׻� ���� �ٶ󺸵��� ���
	UpdateShotDirection(enemy);
	UpdateShotPoint();
	UpdateSatellite(dTime, enemy);

	m_Texture->SetRotation(GetShotDirection());

	//�̵��� ��ų����
	UpdateMotion(dTime, NNInputSystem::GetInstance()->GetSkillKeyInput(), NNInputSystem::GetInstance()->GetDirectionKeyInput());
	SkillCasting(dTime, enemy, map, NNInputSystem::GetInstance()->GetSkillKeyInput());

	//��Ŷ ����
// 	if ( !GNetHelper->IsPeerLinked() )
// 		return ;

	PacketKeyStatus sendPkt ;
	sendPkt.mSequence = framenum ;
	sendPkt.mDirectionStatus = (short)NNInputSystem::GetInstance()->GetDirectionKeyInput();
	sendPkt.mSkillStatus = (short)NNInputSystem::GetInstance()->GetSkillKeyInput();

	GNetHelper->SendKeyStatus(sendPkt) ;
}

void CMaincharacter::UpdateByPeer( float dTime, CMaincharacter* enemy, CMainMap* map, int framenum )
{
	UpdateShotDirection(enemy);
	UpdateShotPoint();

	m_Texture->SetRotation(GetShotDirection());

// 	if ( !GNetHelper->IsPeerLinked() )
// 		return ;

	/// P2P ������ �޾Ƽ� ���� ������Ʈ
	PacketKeyStatus recvPkt ;
	GNetHelper->RecvKeyStatus(recvPkt) ;

	if ( recvPkt.mSequence != framenum )
	{
		/// ���� �ɸ��� ������ ������ ���̴�..
		assert(false) ;
	}

	UpdateMotion(dTime, (EInputSetUp)recvPkt.mSkillStatus, (EInputSetUp)recvPkt.mDirectionStatus);
	SkillCasting(dTime, enemy, map, (EInputSetUp)recvPkt.mSkillStatus);
}

void CMaincharacter::UpdateMotion(float dTime, EInputSetUp skill_key, EInputSetUp move_key)
{
	if (skill_key == CHANGE_SPEED)
	{
		SetSpeed(CHAR_FAST_SPEED);
	}
	else
	{
		SetSpeed(CHAR_SPEED);
	}

	//�Է¿� ���� ĳ������ �̵�
	switch (move_key)
	{
	case UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(270), GetSpeed()*NNDegreeToY(270)) * dTime );
		break;
	case DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(90), GetSpeed()*NNDegreeToY(90)) * dTime );
		break;
	case LEFT:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(180), GetSpeed()*NNDegreeToY(180)) * dTime );
		break;
	case RIGHT:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(0), GetSpeed()*NNDegreeToY(0)) * dTime );
		break;
	case LEFT_UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(225), GetSpeed()*NNDegreeToY(225))*dTime );
		break;
	case LEFT_DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(135), GetSpeed()*NNDegreeToY(135)) * dTime );
		break;
	case RIGHT_UP:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(315), GetSpeed()*NNDegreeToY(315))* dTime );
		break;
	case RIGHT_DOWN:
		SetPosition( GetPosition() + NNPoint(GetSpeed()*NNDegreeToX(45), GetSpeed()*NNDegreeToY(45)) * dTime );
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////
//								 skillcasting									 //
///////////////////////////////////////////////////////////////////////////////////

void CMaincharacter::SkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key)
{
	switch (GetStage())
	{
	case FIRST_STAGE_CHAR:
		FirstStageSkillCasting(dTime, enemy, map, skill_key);
		break;
	default:
		break;
	}
}

void CMaincharacter::FirstStageSkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map, EInputSetUp skill_key)
{
	switch (NNInputSystem::GetInstance()->GetSkillKeyInput())
	{
	case SKILL_KEY_ONE:
		if ( GetCost() >= SHOT_BULLET_COST )
		{
			CBulletManager::GetInstance()->ShotBullet(this, NORMAL_BULLET);
			SetCost( GetCost() - SHOT_BULLET_COST );
		}
		break;
	case SKILL_KEY_TWO:
		if ( GetCost() >= SHOT_ACCELBULLET_COST )
		{
			CBulletManager::GetInstance()->ShotBullet(this, ACCEL_BULLET);
			SetCost( GetCost() - SHOT_ACCELBULLET_COST );
		}
		break;
	case SKILL_KEY_THREE:
		if ( GetCost() >= SECTOR_SINGLE_COST*20 )
		{
			CBulletManager::GetInstance()->ShotSectorMixBullets(this, ACCEL_BULLET, NORMAL_BULLET);
			SetCost( GetCost() - SECTOR_SINGLE_COST*20 );
		}
		break;
	case SKILL_KEY_FOUR:
		if ( GetCost() >= TORNADO_SINGLE_COST*6 )
		{
			CBulletManager::GetInstance()->ShotTornadoBullets(this, 6);
			SetCost( GetCost() - TORNADO_SINGLE_COST*6 );
		}
		break;
	case SKILL_KEY_FIVE:
		if ( GetCost() >= SETUP_SATELLITE_COST )
		{
			SetupSatellite();
			SetCost(GetCost() - SETUP_SATELLITE_COST);
		}
		break;
	case SKILL_KEY_SIX:
		if (GetCost() >= SL_SECTORNORMAL_COST)
		{
			ShotSLSectorNormalBullet();
			SetCost(GetCost() - SL_SECTORNORMAL_COST);
		}
		break;
	}
}

//**************************************************************
//                         Satellite
//**************************************************************
void CMaincharacter::SetupSatellite()
{
	CSatellite* pSatellite = GetSatellite();
	pSatellite->SetPosition(GetPosition());
}

void CMaincharacter::UpdateSatellite(float dTime , CMaincharacter* Enemy)
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			m_pSatelliteArray[i]->Update(dTime, Enemy);
		}
	}
}

CSatellite * CMaincharacter::GetSatellite()
{
	++m_SatelliteIndex;
	m_SatelliteIndex %= MAX_SATELLITE_NUM;
	m_pSatelliteArray[m_SatelliteIndex]->SetVisible(true);

	return m_pSatelliteArray[m_SatelliteIndex];
}

void CMaincharacter::ShotSLSectorNormalBullet()
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			CBulletManager::GetInstance()->ShotSectorBullets(m_pSatelliteArray[i], NORMAL_BULLET);
		}
	}
}

void CMaincharacter::DestroySatellite()
{
	for (int i = 0; i < MAX_SATELLITE_NUM; ++i)
	{
		if (m_pSatelliteArray[i]->IsVisible())
		{
			m_pSatelliteArray[i]->SetVisible(false);
			m_pSatelliteArray[i]->InitMember();
		}
	}
}
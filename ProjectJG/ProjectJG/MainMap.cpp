#include "NNConfig.h"
#include "MainMap.h"
#include "GameOption.h"
#include "NNSprite.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Fairy.h"
#include "ItemBox.h"
#include "Camera.h"
#include "SubChar.h"
#include "PacketHandler.h"

#include "NNAnimation.h"
#include "NNInputSystem.h"		// for � �׽�Ʈ
#include "NNApplication.h"
#include "NNNetworkSystem.h"
#include "PacketHandler.h"
#include "UImanager.h"


CMainMap::CMainMap(ENetworkMode GameMode)
{
	m_Width = MAIN_MAP_WIDTH;
	m_Height = MAIN_MAP_HEIGHT;

	// �� ��� �̹���
	// ���ڿ� �迭�� ���� �����ؾ���
	m_BackGround = NNAnimation::Create( 40,	0.2f,	
		L"Sprite/background/IMG00000.jpg",
		L"Sprite/background/IMG00001.jpg",
		L"Sprite/background/IMG00002.jpg",
		L"Sprite/background/IMG00003.jpg",
		L"Sprite/background/IMG00004.jpg",
		L"Sprite/background/IMG00005.jpg",
		L"Sprite/background/IMG00006.jpg",
		L"Sprite/background/IMG00007.jpg",
		L"Sprite/background/IMG00008.jpg",
		L"Sprite/background/IMG00009.jpg",
		L"Sprite/background/IMG00010.jpg",
		L"Sprite/background/IMG00011.jpg",
		L"Sprite/background/IMG00012.jpg",
		L"Sprite/background/IMG00013.jpg",
		L"Sprite/background/IMG00014.jpg",
		L"Sprite/background/IMG00015.jpg",
		L"Sprite/background/IMG00016.jpg",
		L"Sprite/background/IMG00017.jpg",
		L"Sprite/background/IMG00018.jpg",
		L"Sprite/background/IMG00019.jpg",
		L"Sprite/background/IMG00020.jpg",
		L"Sprite/background/IMG00021.jpg",
		L"Sprite/background/IMG00022.jpg",
		L"Sprite/background/IMG00023.jpg",
		L"Sprite/background/IMG00024.jpg",
		L"Sprite/background/IMG00025.jpg",
		L"Sprite/background/IMG00026.jpg",
		L"Sprite/background/IMG00027.jpg",
		L"Sprite/background/IMG00028.jpg",
		L"Sprite/background/IMG00029.jpg",
		L"Sprite/background/IMG00030.jpg",
		L"Sprite/background/IMG00031.jpg",
		L"Sprite/background/IMG00032.jpg",
		L"Sprite/background/IMG00033.jpg",
		L"Sprite/background/IMG00034.jpg",
		L"Sprite/background/IMG00035.jpg",
		L"Sprite/background/IMG00036.jpg",
		L"Sprite/background/IMG00037.jpg",
		L"Sprite/background/IMG00038.jpg",
		L"Sprite/background/IMG00039.jpg");
	
	m_BackGround->SetImageWidth( GetWidth() );
	m_BackGround->SetImageHeight( GetHeight() );
	AddChild( m_BackGround );

	// �÷��̾� ���� �� ����ĳ���� ����
	CSubChar* subchar_1;
	CSubChar* subchar_2;
	if (GameMode == SERVER_MODE || GameMode == TEST_MODE)
	{
		subchar_1 = new CSubChar(YUKARI);
		m_Player1 = new CMaincharacter(RAYMU);
		m_Player1->SetSubChar(subchar_1);

		subchar_2 = new CSubChar(ALICE);
		m_Player2 = new CMaincharacter(MARISA);
		m_Player2->SetSubChar(subchar_2);
	}
	else
	{
		subchar_1 = new CSubChar(ALICE);
		m_Player1 = new CMaincharacter(MARISA);
		m_Player1->SetSubChar(subchar_1);

		subchar_2 = new CSubChar(YUKARI);
		m_Player2 = new CMaincharacter(RAYMU);
		m_Player2->SetSubChar(subchar_2);
	}

	subchar_1->SetVisible(false);
	subchar_2->SetVisible(false);

	// addchild������ ���� ������ ���� ����
	// ���� �ε�
	for (int i = 0; i <MAX_FAIRY_NUM; ++i)
	{
		m_Player1->GetFairyArray()[i] = new CFairy;
		AddChild(m_Player1->GetFairyArray()[i]);
		m_Player1->GetFairyArray()[i]->SetVisible(false);
	}
	for (int i = 0; i <MAX_FAIRY_NUM; ++i)
	{
		m_Player2->GetFairyArray()[i] = new CFairy;
		AddChild(m_Player2->GetFairyArray()[i]);
		m_Player2->GetFairyArray()[i]->SetVisible(false);
	}

	AddChild( subchar_1 );
	AddChild( subchar_2 );
	AddChild( m_Player1 );
	AddChild( m_Player2 );


	// �÷��̾� ��ġ
	// (0,0) �� ���� �߽�. �÷��̾� 1�� �Ʒ� ȭ���� �����, �÷��̾� 2�� �� ȭ���� ����� ��ġ�Ѵ�.
	m_Player1->SetPosition( 0.f, GetBotLine() *0.5f );
	m_Player2->SetPosition( 0.f, GetTopLine() *0.5f );

	// �Ѿ� ����
	for (int i = 0 ; i < MAX_BULLET_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetBulletArray()[i] = new CBullet;
		AddChild( CBulletManager::GetInstance()->GetBulletArray()[i] );
		CBulletManager::GetInstance()->GetBulletArray()[i]->SetVisible(false);
	}

	m_ItemBox = new CItemBox;
	m_ItemBox->SetVisible(false);
	AddChild(m_ItemBox);

	m_Camera = new CCamera();

	// cost
	m_CostPerSecond = COST_INCREASE_SPEED;

	m_TimeToHitCheckWait = 0.f;
	m_GameResult = GAME_NOT_END;
	m_PlayTimeSum = 0.f;
	m_TimeForSummonItemBox = 0.f;
}

void CMainMap::Init()
{
	m_TimeToHitCheckWait = 0.f;
	m_GameResult = GAME_NOT_END;
	m_PlayTimeSum = 0.f;
	m_TimeForSummonItemBox = 0.f;

	m_Player1->Init();
	m_Player2->Init();
	m_Player1->SetPosition( 0.f, GetBotLine()*0.5f );
	m_Player2->SetPosition( 0.f, GetTopLine()*0.5f );

	CBulletManager::GetInstance()->InitAllBullet();

	m_Camera->SetPosition(0.f, 0.f);
}

CMainMap::~CMainMap(void)
{
	SafeDelete(m_Camera);
}

void CMainMap::Render()
{

	if ( m_Visible == false ) return;

	m_Matrix = D2D1::Matrix3x2F::Translation( -m_Center.GetX() , -m_Center.GetY() )* 
		D2D1::Matrix3x2F::Translation( -m_Camera->GetPositionX(), -m_Camera->GetPositionY() ) *
		D2D1::Matrix3x2F::Scale( m_ScaleX, m_ScaleY ) *
		D2D1::Matrix3x2F::Scale( m_Camera->GetScaleX(), m_Camera->GetScaleY() ) *
		D2D1::Matrix3x2F::Rotation( m_Rotation ) *
		D2D1::Matrix3x2F::Rotation( m_Camera->GetRotation() ) *
		D2D1::Matrix3x2F::Translation( m_Position.GetX(), m_Position.GetY() );

	if( m_pParent )
	{
		m_Matrix = m_Matrix * m_pParent->GetMatrix();
	}

	for (const auto& child : m_ChildList )
	{
		child->Render();
	}
}

void CMainMap::Update( float dTime, CFrame* frame )
{
	m_PlayTimeSum += dTime;

#ifdef _DEBUG
	UImanager::GetInstance()->SetTime(m_PlayTimeSum);
#endif	

	m_BackGround->Update(dTime);

	//��밡 �¾Ҵٰ� ��Ŷ�̿��� �¾Ҵٰ� ǥ��
	if (m_GameMode && m_Player2->GetPacketHandler()->m_PacketKeyStatus.mHitCheck == true)
	{
		m_Player2->SetHit(true);
	}

	//���� ����� ����
	if (m_Player1->IsHit() || m_Player2->IsHit())
	{
		m_TimeToHitCheckWait += dTime;

		if (m_Player1->IsHit())
			m_Player1->UpdateDeadAnimation(dTime);
		if (m_Player2->IsHit())
			m_Player2->UpdateDeadAnimation(dTime);

		if (m_TimeToHitCheckWait > 2.0f)
		{
			if (m_Player1->IsHit() && m_Player2->IsHit())
			{
				m_GameResult = GAME_RESULT_DRAW;
			}
			else if (m_Player1->IsHit())
			{
				m_GameResult = GAME_RESULT_LOSE;
			}
			else if (m_Player2->IsHit())
			{
				m_GameResult = GAME_RESULT_WIN;
			}
		}
	}

	// cost
	GetPlayer1()->SetCost( GetPlayer1()->GetCost() + m_CostPerSecond*dTime );
	GetPlayer2()->SetCost( GetPlayer2()->GetCost() + m_CostPerSecond*dTime );

	//�Ѿ��� ������Ʈ�� ������Ÿ�� üũ
	CBulletManager::GetInstance()->UpdateObj(dTime, m_Player2, this);

	//ĳ���� ������Ʈ
	if (!m_Player1->IsHit())
		m_Player1->Update(dTime, m_Player2, this, m_GameMode);
	if (!m_Player2->IsHit())
		m_Player2->UpdateByPeer(dTime, m_Player1, this, m_GameMode);

	//�Ѿ˰� ĳ������ �浹üũ
	if(CBulletManager::GetInstance()->CharacterHitCheck(m_Player1))
	{
		m_Player1->SetHit( true );
		//������ ��Ŷ�� �¾Ҵٰ� �˷���
		if (m_GameMode)
		{
			m_Player1->GetPacketHandler()->m_PacketKeyStatus.mHitCheck = true;
			m_Player1->SendPacket();
		}
	}

	//�ʰ� ĳ������ �浹üũ
	SetPlayerMoveArea(m_Player1, frame);
	SetPlayerMoveArea(m_Player2, frame);

	//SummonItemBox(dTime);
}

void CMainMap::SetPlayerMoveArea( CMaincharacter * Player, CFrame* frame )
{
	// ĳ���Ͱ� ������ �� �ִ� ����. �������� ȭ�� ������ ���� �ʵ��� �Ѵ�.
	float leftline	= this->GetLeftLine()	+ frame->GetPositionX()	+ frame->GetLeftLine()	+ NNApplication::GetInstance()->GetLeftLine();
	float rightline	= this->GetRightLine()	+ frame->GetPositionX()	+ frame->GetRightLine()	- NNApplication::GetInstance()->GetRightLine();
	float topline	= this->GetTopLine()	+ frame->GetPositionY()	+ frame->GetTopLine()	+ NNApplication::GetInstance()->GetTopLine();
	float botline	= this->GetBotLine()	+ frame->GetPositionY()	+ frame->GetBotLine()	- NNApplication::GetInstance()->GetBotLine();

	if (Player->GetPositionX() < leftline)
	{
		Player->SetPosition(NNPoint(leftline, Player->GetPositionY()));
	}
	if (Player->GetPositionX() > rightline)
	{
		Player->SetPosition(NNPoint(rightline, Player->GetPositionY()));
	}
	if (Player->GetPositionY() > botline)
	{
		Player->SetPosition(NNPoint(Player->GetPositionX(), botline));
	}
	if (Player->GetPositionY() < topline)
	{
		Player->SetPosition(NNPoint(Player->GetPositionX(),topline));
	}
}

void CMainMap::SummonItemBox(float dTime)
{
// 	m_TimeForSummonItemBox += dTime;
// 
// 	float leftline = GetLeftLine();
// 	float rightline = GetRightLine();
// 	float botline = GetBotLine();
// 	float topline = GetTopLine();
// 
// 	if (m_TimeForSummonItemBox > 1.0f)
// 	{
// 
// 
// 
// 		m_TimeForSummonItemBox = 0.f;
// 	}

	m_ItemBox->SetPosition(0.f, 0.f);
	m_ItemBox->SetVisible(true);
	m_ItemBox->Update(dTime);
	
}

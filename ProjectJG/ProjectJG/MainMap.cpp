#include "NNConfig.h"
#include "MainMap.h"
#include "GameOption.h"
#include "NNSprite.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Satellite.h"
#include "Asteroid.h"
#include "NetManager.h"
#include "Camera.h"

#include "NNInputSystem.h"		// for � �׽�Ʈ


CMainMap::CMainMap(void)
{
	++m_CurrentFrame;

	m_Width = MAIN_MAP_WIDTH;
	m_Height = MAIN_MAP_HEIGHT;

	m_MainFrame = NNRect::Create(m_Width, m_Height);
	m_MainFrame->SetPosition(0.f,0.f);
	m_MainFrame->SetColor(255.f, 255.f, 255.f);
	AddChild(m_MainFrame);

	
	// �� ��� �̹���
	m_BackGround = NNSprite::Create( MAIN_MAP_BACKGROUND_IMAGE );
	m_BackGround->SetImageWidth( GetWidth() );
	m_BackGround->SetImageHeight( GetHeight() );
	AddChild( m_BackGround );

	//�÷��̾� ����
	m_Player1 = new CMaincharacter;
	m_Player2 = new CMaincharacter;

	m_Player1->SetPosition( 0.f, GetBotLine() *0.5f );
	m_Player2->SetPosition( 0.f, GetTopLine() *0.5f );

	AddChild( m_Player1 );
	AddChild( m_Player2 );

	//�Ѿ� ����
	for (int i = 0 ; i < MAX_BULLET_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetBulletArray()[i] = new CBullet;
		AddChild( CBulletManager::GetInstance()->GetBulletArray()[i] );
		CBulletManager::GetInstance()->GetBulletArray()[i]->SetVisible(false);
	}

	//� �ε�
	for (int i = 0 ; i < MAX_ASTEROID_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetAsteroidArray()[i] = new CAsteroid;
		AddChild( CBulletManager::GetInstance()->GetAsteroidArray()[i] );
		CBulletManager::GetInstance()->GetAsteroidArray()[i]->SetVisible(false);
	}

	//�ΰ����� �ε�
	for (int i = 0; i <MAX_SATELLITE_NUM; ++i)
	{
		m_Player1->GetSatelliteArray()[i] = new CSatellite;
		AddChild(m_Player1->GetSatelliteArray()[i]);
		m_Player1->GetSatelliteArray()[i]->SetVisible(false);
	}
	for (int i = 0; i <MAX_SATELLITE_NUM; ++i)
	{
		m_Player2->GetSatelliteArray()[i] = new CSatellite;
		AddChild(m_Player2->GetSatelliteArray()[i]);
		m_Player2->GetSatelliteArray()[i]->SetVisible(false);
	}

	m_Camera = new CCamera();
}


CMainMap::~CMainMap(void)
{
	delete m_Camera;
}

void CMainMap::Render()
{
	if ( m_Visible == false ) return;

	m_Matrix = D2D1::Matrix3x2F::Translation( -m_Center.GetX() , -m_Center.GetY() )* 
		D2D1::Matrix3x2F::Translation( - m_Camera->GetPositionX(), - m_Camera->GetPositionY() ) *
		D2D1::Matrix3x2F::Rotation( m_Rotation ) *
		D2D1::Matrix3x2F::Scale( m_ScaleX, m_ScaleY ) *
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

void CMainMap::Update( float dTime )
{
	//�Ѿ� �� ������Ʈ�� ������Ʈ�� ������Ÿ�� äũ
	CBulletManager::GetInstance()->UpdateObj(dTime, m_Player2, this);

	//ĳ���� ������Ʈ
	if (m_GameMode == TEST_MODE)
	{	
		m_Player1->Update(dTime, m_Player2, this);
	}
	else
	{
		m_Player1->Update(dTime, m_Player2, this, m_CurrentFrame);
		m_Player2->UpdateByPeer(dTime, m_Player1, this, m_CurrentFrame);
	}

	//�ʰ� ĳ������ �浹üũ
	SetPlayerMoveArea(m_Player1);
	SetPlayerMoveArea(m_Player2);

	//�Ѿ˰� ĳ������ �浹üũ
	if(CBulletManager::GetInstance()->CharacterHitCheck(m_Player1))
		m_Player1->SetHit( true );
	//�׽�Ʈ����Ȳ�϶��� ���� �浹äũ�� ���� �ʴ´�
	if(m_GameMode && CBulletManager::GetInstance()->CharacterHitCheck(m_Player2))
		m_Player2->SetHit( true );


	//� �׽�Ʈ�� �ڵ�
	if(NNInputSystem::GetInstance()->GetKeyState('P') == KEY_DOWN)
	{
		CBulletManager::GetInstance()->ShotAsteroid(this);
	}
}

void CMainMap::SetPlayerMoveArea(CMaincharacter * Player)
{
	float leftline = GetLeftLine();
	float rightline = GetRightLine();
	float botline = GetBotLine();
	float topline = GetTopLine();

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

bool CMainMap::IsGameEnd()
{
	
	if (m_GameMode && !GNetHelper->IsPeerLinked())
	{
		return true;
	}

	return ( m_Player1->IsHit() || m_Player2->IsHit() );
}

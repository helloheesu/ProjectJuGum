#include "NNConfig.h"
#include "MainMap.h"
#include "GameOption.h"
#include "NNSprite.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Satellite.h"
#include "Asteroid.h"
#include "Camera.h"

#include "NNAnimation.h"
#include "NNInputSystem.h"		// for � �׽�Ʈ
#include "NNApplication.h"


CMainMap::CMainMap(void)
{
	m_Width = MAIN_MAP_WIDTH;
	m_Height = MAIN_MAP_HEIGHT;

	// �簢�� Ʋ ����
	m_MainFrame = NNRect::Create(m_Width, m_Height);
	m_MainFrame->SetPosition(0.f,0.f);
	m_MainFrame->SetColor(255.f, 255.f, 255.f);
	AddChild(m_MainFrame);

	// �� ��� �̹���
	//���ڿ� �迭�� ���� �����ؾ���
	m_BackGround = NNAnimation::Create( 25,	L"Sprite/background/IMG00000.jpg",
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
											L"Sprite/background/IMG00024.jpg"
												);

	m_BackGround->SetImageWidth( GetWidth() );
	m_BackGround->SetImageHeight( GetHeight() );
	AddChild( m_BackGround );

	//�÷��̾� ����
	m_Player1 = new CMaincharacter;
	m_Player2 = new CMaincharacter;

	// cost
	m_CostPerSecond = 5.f;

	// �÷��̾� ��ġ
	// (0,0) �� ���� �߽�. �÷��̾� 1�� �Ʒ� ȭ���� �����, �÷��̾� 2�� �� ȭ���� ����� ��ġ�Ѵ�.
	m_Player1->SetPosition( 0.f, GetBotLine() *0.5f );
	m_Player2->SetPosition( 0.f, GetTopLine() *0.5f );

	AddChild( m_Player1 );
	AddChild( m_Player2 );

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

	//�Ѿ� ����
	for (int i = 0 ; i < MAX_BULLET_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetBulletArray()[i] = new CBullet;
		AddChild( CBulletManager::GetInstance()->GetBulletArray()[i] );
		CBulletManager::GetInstance()->GetBulletArray()[i]->SetVisible(false);
	}

	m_Camera = new CCamera();
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
	m_BackGround->Update(dTime);

	// cost
	GetPlayer1()->SetCost( GetPlayer1()->GetCost() + m_CostPerSecond*dTime );
	GetPlayer2()->SetCost( GetPlayer2()->GetCost() + m_CostPerSecond*dTime );

	//�Ѿ� �� ������Ʈ�� ������Ʈ�� ������Ÿ�� üũ
	CBulletManager::GetInstance()->UpdateObj(dTime, m_Player2, this);

	//�Ѿ˰� ĳ������ �浹üũ
	if(CBulletManager::GetInstance()->CharacterHitCheck(m_Player1))
	{
		m_Player1->SetHit( true );
	}
	//�׽�Ʈ ����� ���� ������ �浹üũ�� ���� �ʴ´�
// 	if(m_GameMode && CBulletManager::GetInstance()->CharacterHitCheck(m_Player2))
// 		m_Player2->SetHit( true );

	//ĳ���� ������Ʈ
	m_Player1->Update(dTime, m_Player2, this, m_GameMode);
	m_Player2->UpdateByPeer(dTime, m_Player1, this, m_GameMode);

	//�ʰ� ĳ������ �浹üũ
	SetPlayerMoveArea(m_Player1, frame);
	SetPlayerMoveArea(m_Player2, frame);

	//� �׽�Ʈ�� �ڵ�
	if(NNInputSystem::GetInstance()->GetKeyState('P') == KEY_DOWN)
	{
		CBulletManager::GetInstance()->ShotAsteroid(this);
	}
}

void CMainMap::SetPlayerMoveArea( CMaincharacter * Player, CFrame* frame )
{
	// ĳ���Ͱ� ������ �� �ִ� ����. �������� ȭ�� ������ ���� �ʵ��� �Ѵ�.
	float leftline = GetLeftLine() - NNApplication::GetInstance()->GetLeftLine() + frame->GetLeftLine();
	float rightline = GetRightLine() - NNApplication::GetInstance()->GetRightLine() + frame->GetRightLine();
	float botline = GetBotLine() - NNApplication::GetInstance()->GetBotLine() + frame->GetBotLine();
	float topline = GetTopLine() - NNApplication::GetInstance()->GetTopLine() + frame->GetTopLine();
	
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
	if ( m_Player1->IsHit() || m_Player2->IsHit())
	{
		return true;
	}

	return false;
}

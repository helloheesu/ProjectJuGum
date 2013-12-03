#include "NNConfig.h"

#include "NNLabel.h"
#include "NNSceneDirector.h"
#include "NNApplication.h"
#include "NNSprite.h"

#include "PlayScene.h"
#include "Maincharacter.h"
#include "BulletManager.h"
#include "MainMenuScene.h"
#include "MainMap.h"
#include "Frame.h"
#include "Camera.h"
#include "UImanager.h"

#include "NetManager.h"

CPlayScene::CPlayScene(void) : m_netsetup(false), m_DoCount(true), m_CountNum(0.f)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	// ���� ���� ��
	m_MainMap = new CMainMap();
	m_MainMap->SetPosition( NNPoint(width *0.5f, height *0.5f) );
	AddChild(m_MainMap);

	// ī�޶� ������
	m_Frame = new CFrame();
	m_Frame->SetPosition( width*0.5f, height*0.5f );
	m_Frame->SetSize( FRAME_WIDTH, FRAME_HEIGHT );
	AddChild( m_Frame );

	//��Ʈ��ũ ���� �޴�
	m_MenuLabel[TEST_MODE] = NNLabel::Create( L"TEST", L"�ü�ü", 40.f );
	m_MenuLabel[TEST_MODE]->SetColor(255.0f, 0.0f, 0.0f);
	m_MenuLabel[TEST_MODE]->SetPosition( width*0.5f + 60.f, height*0.5f );
	AddChild( m_MenuLabel[TEST_MODE] );

	m_MenuLabel[CLIENT_MODE] = NNLabel::Create( L"CLIENT", L"�ü�ü", 40.f );
	m_MenuLabel[CLIENT_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_MenuLabel[CLIENT_MODE]->SetPosition( width*0.5f + 60.f, height*0.5f + 80.f );
	AddChild( m_MenuLabel[CLIENT_MODE] );

	m_MenuLabel[SERVER_MODE] = NNLabel::Create( L"SERVER", L"�ü�ü", 40.f );
	m_MenuLabel[SERVER_MODE]->SetColor(0.0f, 0.0f, 0.0f);
	m_MenuLabel[SERVER_MODE]->SetPosition( width*0.5f + 60.f, height*0.5f + 160.f );
	AddChild( m_MenuLabel[SERVER_MODE] );

	//ī��Ʈ�ٿ��� ���� ��
	m_CountNumLabel_3 = NNLabel::Create(L"3", L"�ü�ü", 40.f);
	m_CountNumLabel_3->SetColor(255.0f, 0.0f, 0.0f);
	m_CountNumLabel_3->SetPosition( NNPoint(width *0.5f, height *0.5f) );
	m_CountNumLabel_3->SetVisible(false);
	AddChild( m_CountNumLabel_3 );

	m_CountNumLabel_2 = NNLabel::Create(L"2", L"�ü�ü", 40.f);
	m_CountNumLabel_2->SetColor(255.0f, 0.0f, 0.0f);
	m_CountNumLabel_2->SetPosition( NNPoint(width *0.5f, height *0.5f) );
	m_CountNumLabel_2->SetVisible(false);
	AddChild( m_CountNumLabel_2 );

	m_CountNumLabel_1 = NNLabel::Create(L"1", L"�ü�ü", 40.f);
	m_CountNumLabel_1->SetColor(255.0f, 0.0f, 0.0f);
	m_CountNumLabel_1->SetPosition( NNPoint(width *0.5f, height *0.5f) );
	m_CountNumLabel_1->SetVisible(false);
	AddChild( m_CountNumLabel_1 );

	m_KeyOn = 0;
}

CPlayScene::~CPlayScene(void)
{
	SafeDelete(GNetHelper);
}

void CPlayScene::Render()
{
	NNScene::Render();
	UImanager::GetInstance()->Render();
}

void CPlayScene::Update( float dTime )
{
	//��Ʈ��ũ ���ø޴�
	if (!m_netsetup)
	{
		if(!NetworkSetMenu())
		{
			return;
		}
		m_netsetup = true;
		return;
	}

	//3���� ī��Ʈ�ٿ� �� ���� ����
	if (m_DoCount)
	{
		//3���� ī��Ʈ �ٿ�
		CountDown(dTime);
		return;
	}
	
	
	// camera move. �÷��̾ ������ ������ ���� ī�޶� ���� �����δ�.
	CameraMove( m_MainMap->GetPlayer1(), dTime );

	// UI update
	UImanager::GetInstance()->Update( dTime, m_MainMap->GetPlayer1(), m_MainMap->GetPlayer2() );

	// ��� ���� �÷��� ���� ó���� ���� �ʿ��� �Ѵ�.
	m_MainMap->Update( dTime, m_Frame );
	if ( m_MainMap->IsGameEnd() )
		EndGame();
}

bool CPlayScene::CircleToCircleHitCheck(NNPoint point_A, float radius_A, NNPoint point_B, float radius_B) 
{
	if((radius_A + radius_B) > point_A.GetDistance(point_B))
	{
		return true;
	}
	return false;
}

void CPlayScene::EndGame()
{
	//����ȭ�� ���� 3�ʰ��� ����
	Sleep(3000);
	NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );
	return;
}

void CPlayScene::CountDown(float dTime)
{
	m_CountNum += dTime;

	if (m_CountNum <= 1.f)
	{
		m_CountNumLabel_3->SetVisible(true);
	}
	
	if (1.f < m_CountNum && m_CountNum <= 2.f)
	{
		m_CountNumLabel_3->SetVisible(false);
		m_CountNumLabel_2->SetVisible(true);
	}

	if (2.f < m_CountNum && m_CountNum <= 3.f)
	{
		m_CountNumLabel_2->SetVisible(false);
		m_CountNumLabel_1->SetVisible(true);
	}

	if( m_CountNum > 3.f )
	{
		m_CountNumLabel_1->SetVisible(false);
		m_DoCount = false;
	}
}

bool CPlayScene::NetworkSetMenu()
{
	//ip
	char* serverIpAddr = "127.0.0.1";
	//char* serverIpAddr = "10.73.42.57";
	//char* serverIpAddr = "10.73.43.123";
	//char* serverIpAddr = "10.73.42.217";
	//char* serverIpAddr = "10.73.42.180";

	//�޴�
	m_MenuLabel[m_KeyOn]->SetColor( 0.f, 0.f, 0.f);	
	if ( NNInputSystem::GetInstance()->GetMainMenuInput() == UP 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == LEFT )
	{
		--m_KeyOn;
	}
	else if ( NNInputSystem::GetInstance()->GetMainMenuInput() == DOWN 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == RIGHT )
	{
		++m_KeyOn;
	}
	m_KeyOn = (m_KeyOn + NET_MENU_LAST) % NET_MENU_LAST;
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 0.f, 0.f );


	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
	{
		switch (m_KeyOn)
		{
		case TEST_MODE:
			m_MainMap->SetGameMode(TEST_MODE);
			break;

		case CLIENT_MODE:

			GNetHelper = new NetHelper(false, serverIpAddr) ;

			//�����ʱ�ȭ
			if ( !GNetHelper->Initialize() )
			{
				MessageBox(NULL, L"NetHelper::Initialize()", L"ERROR", MB_OK) ;
				return false;
			}

			//����õ�
			if ( !GNetHelper->DoHandShake() )
			{
				return false;
			}

			//���� �� ĳ���͸� ��ġ�� ��ġ
			m_MainMap->GetPlayer1()->SetPosition( 0.f, m_MainMap->GetBotLine() *0.5f );
			m_MainMap->GetPlayer2()->SetPosition( 0.f, m_MainMap->GetTopLine() *0.5f );

			m_MainMap->SetGameMode(CLIENT_MODE);
			break;

		case SERVER_MODE:
			GNetHelper = new NetHelper(true, serverIpAddr) ;

			//���� �ʱ�ȭ
			if ( !GNetHelper->Initialize() )
			{
				MessageBox(NULL, L"NetHelper::Initialize()", L"ERROR", MB_OK) ;
				return false;
			}

			//���ǻ� IP�ּҸ� �ҷ��´�
			GNetHelper->GetHostIP();

			//����õ�
			if ( !GNetHelper->DoHandShake() )
			{
				return false;
			}

			//���� �� ĳ���͸� ��ġ�� ��ġ
			m_MainMap->GetPlayer1()->SetPosition( 0.f, m_MainMap->GetTopLine() *0.5f );
			m_MainMap->GetPlayer2()->SetPosition( 0.f, m_MainMap->GetBotLine() *0.5f );

			m_MainMap->SetGameMode(SERVER_MODE);
			break;
		default:
			break;
		}

		//�޴��� �Ⱥ��̵��� ����
		for (int i = NET_MENU_FIRST; i < NET_MENU_LAST; ++i)
		{
			m_MenuLabel[i]->SetVisible(false);
		}

		return true;
	}
	return false;
}


void CPlayScene::CameraMove( CMaincharacter* Player, float dTime )
{
	float leftline = m_Frame->GetLeftLine();
	float rightline = m_Frame->GetRightLine();
	float botline = m_Frame->GetBotLine();
	float topline = m_Frame->GetTopLine();

	CCamera* camera = m_MainMap->GetCamera();

	if (Player->GetPositionX() - camera->GetPositionX() < leftline)
	{
		camera->SetPosition( Player->GetPositionX() - leftline , camera->GetPositionY() );
	}
	if (Player->GetPositionX() - camera->GetPositionX() > rightline)
	{
		camera->SetPosition( Player->GetPositionX() - rightline, camera->GetPositionY() );
	}
	if (Player->GetPositionY() - camera->GetPositionY() > botline)
	{
		camera->SetPosition( camera->GetPositionX(), Player->GetPositionY() - botline );
	}
	if (Player->GetPositionY() - camera->GetPositionY() < topline)
	{
		camera->SetPosition( camera->GetPositionX(), Player->GetPositionY() - topline );
	}
}



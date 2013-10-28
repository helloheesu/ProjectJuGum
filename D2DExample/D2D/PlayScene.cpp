#include "PlayScene.h"
#include "MainMenuScene.h"

CPlayScene::CPlayScene(void) : 
	m_BulletIndex1(0), m_BulletIndex2(0)
{
	m_Map = CMainMap::Create();
	AddChild(m_Map);
	m_Map->SetPosition(NNPoint(640.f, 400.f));

	m_Player1 = CMaincharacter::Create();
	m_Player2 = CMaincharacter::Create();

	m_Player1->SetMoveArea(640.f-m_Map->GetMainFrame()->GetWidth()/2, 640.f+m_Map->GetMainFrame()->GetWidth()/2, 400.f-m_Map->GetMainFrame()->GetHeight()/2, 400.f+m_Map->GetMainFrame()->GetHeight()/2);
	m_Player2->SetMoveArea(640.f-m_Map->GetMainFrame()->GetWidth()/2, 640.f+m_Map->GetMainFrame()->GetWidth()/2, 400.f-m_Map->GetMainFrame()->GetHeight()/2, 400.f+m_Map->GetMainFrame()->GetHeight()/2);

	m_Player2->SetKeyUp('W');
	m_Player2->SetKeyDown('S');
	m_Player2->SetKeyLeft('A');
	m_Player2->SetKeyRight('D');

	AddChild( m_Player1 );
	AddChild( m_Player2 );

	for(int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		m_Bullet1[i] = CBullet::Create();
		AddChild( m_Bullet1[i] );
	}

	for(int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		m_Bullet2[i] = CBullet::Create();
		m_Bullet2[i]->SetDirection(90);
		AddChild( m_Bullet2[i] );
	}

	m_Player1->SetPosition(NNPoint(640.f, 700.f));
	m_Player2->SetPosition(NNPoint(640.f, 100.f));

	// FPS
	m_FPSLabel = NNLabel::Create( L"FPS : ", L"���� ���", 20.f );
	m_FPSLabel->SetPosition( 0.f, 0.f );
	AddChild( m_FPSLabel );

	m_SumTime = 0;

}

CPlayScene::~CPlayScene(void)
{
}

void CPlayScene::Render()
{
	NNScene::Render();
}
void CPlayScene::Update( float dTime )
{
	// FPS
	m_SumTime += dTime;
	// 1�ʴ� �ʹ� ��淡 0.2�ʷ� ����
	if ( m_SumTime > 0.2 )
	{
	swprintf_s( m_FPS, _countof(m_FPS), L"FPS : %0.3f\n", NNApplication::GetInstance()->GetFPS() );
	m_FPSLabel->SetString(m_FPS);
		// ���� �� �� �߿� ��� �� �� ���� �� �𸣰ڴ� �̤�
		// 0.2 �� �� �� ��� �� ������ ����(=0) �Ǵ� �� ���� ��.
		 m_SumTime = 0;
		// m_SumTime -= 0.2;

#ifdef _DEBUG
		 // ���� 0.2�� ���� ���� ���� ��ġ ����� �� �Ǵ� �� ó�� ����.. �׷��� �ֿܼ��� ��� ���� ���ϱ� ����
		 printf_s("FPS : %0.3f\n", NNApplication::GetInstance()->GetFPS() );
#endif // _DEBUG	
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SPACE ) == KEY_DOWN && m_BulletIndex1 < MAX_BULLET_NUM )
	{
		m_Bullet1[m_BulletIndex1]->SetPosition( m_Player1->GetPosition() );
		++m_BulletIndex1;
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SHIFT ) == KEY_DOWN && m_BulletIndex2 < MAX_BULLET_NUM )
	{
		m_Bullet2[m_BulletIndex2]->SetPosition( m_Player2->GetPosition() );
		++m_BulletIndex2;
	}

	for (int i = 0; i < m_BulletIndex1; ++i)
	{
		if(HitCheck(m_Bullet1[i]->GetPosition(), m_Bullet1[i]->GetMainCircle()->GetRadius(), m_Player2->GetPosition(), m_Player2->GetMainCircle()->GetRadius()))
		{
			NNSceneDirector::GetInstance()->ChangeScene(CMainMenuScene::Create());
		}
	}

	for (int i = 0; i < m_BulletIndex2; ++i)
	{
		if(HitCheck(m_Bullet2[i]->GetPosition(), m_Bullet2[i]->GetMainCircle()->GetRadius(), m_Player1->GetPosition(), m_Player1->GetMainCircle()->GetRadius()))
		{
			NNSceneDirector::GetInstance()->ChangeScene(CMainMenuScene::Create());
		}
	}

	for (int i = 0; i < m_BulletIndex1; ++i)
	{
		m_Bullet1[i]->Update(dTime);
	}

	for (int i = 0; i < m_BulletIndex2; ++i)
	{
		m_Bullet2[i]->Update(dTime);
	}
	
	m_Player1->Update(dTime);
	m_Player2->Update(dTime);
}

bool CPlayScene::HitCheck(NNPoint Apoint, float Aradius, NNPoint Bpoint, float Bradius)
{
	if((Aradius + Bradius) > sqrt((Apoint.GetX()-Bpoint.GetX())*(Apoint.GetX()-Bpoint.GetX())+(Apoint.GetY()-Bpoint.GetY()*(Apoint.GetY()-Bpoint.GetY()))))
	{
		return true;
	}
	return false;
}
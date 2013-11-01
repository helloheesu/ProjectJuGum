#include "PlayScene.h"
#include "MainMenuScene.h"

CPlayScene::CPlayScene(void) : 
	m_BulletIndex1(0), m_BulletIndex2(0)
{
	//�ʻ���
	m_Map = new CMainMap;
	m_Map->SetPosition(NNPoint(640.f, 400.f));
	AddChild(m_Map);

	//�÷��̾� ����
	m_Player1 = new CMaincharacter;
	m_Player2 = new CMaincharacter;

	m_Player2->SetKeyUp('W');
	m_Player2->SetKeyDown('S');
	m_Player2->SetKeyLeft('A');
	m_Player2->SetKeyRight('D');

	m_Player1->SetPosition(NNPoint(640.f, 700.f));
	m_Player2->SetPosition(NNPoint(640.f, 100.f));

	AddChild( m_Player1 );
	AddChild( m_Player2 );

	//�Ѿ� ����
	for(int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		m_Bullet1[i] = new CBullet;
		AddChild( m_Bullet1[i] );
	}

	for(int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		m_Bullet2[i] = new CBullet;
		m_Bullet2[i]->SetDirection(90);
		AddChild( m_Bullet2[i] );
	}

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
	}

	//�����Է�
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SPACE ) == KEY_DOWN && m_BulletIndex1 < MAX_BULLET_NUM )
	{
		m_Bullet1[m_BulletIndex1]->SetPosition( m_Player1->GetPosition() );
		++m_BulletIndex1;
		if (m_BulletIndex1 >= MAX_BULLET_NUM)
		{
			m_BulletIndex1 = 0;
		}
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SHIFT ) == KEY_DOWN && m_BulletIndex2 < MAX_BULLET_NUM )
	{
		m_Bullet2[m_BulletIndex2]->SetPosition( m_Player2->GetPosition() );
		++m_BulletIndex2;
		if (m_BulletIndex2 >= MAX_BULLET_NUM)
		{
			m_BulletIndex2 = 0;
		}
	}

	//�Ѿ��� �̵�
	for (int i = 0; i < m_BulletIndex1; ++i)
	{
		m_Bullet1[i]->Update(dTime);
	}

	for (int i = 0; i < m_BulletIndex2; ++i)
	{
		m_Bullet2[i]->Update(dTime);
	}

	//ĳ������ �̵�
	m_Player1->Update(dTime);
	m_Player2->Update(dTime);

	//�ʰ� ĳ������ �浹üũ
	SetPlayerMoveArea(m_Player1);
	SetPlayerMoveArea(m_Player2);

	//�Ѿ˰� ĳ������ �浹üũ
	for (int i = 0; i < m_BulletIndex1; ++i)
	{
		if(m_Bullet1[i]->CharacterHitCheck(m_Player2))
		{
			NNSceneDirector::GetInstance()->ChangeScene(new CMainMenuScene);
		}
	}
	for (int i = 0; i < m_BulletIndex2; ++i)
	{
		if(m_Bullet2[i]->CharacterHitCheck(m_Player1))
		{
			NNSceneDirector::GetInstance()->ChangeScene(new CMainMenuScene);
		}
	}
	
	//�Ѿ��� ������Ÿ�� ó��
	for (int i = 0; i < m_BulletIndex1; ++i)
	{
		SetBolletLifeTime(m_Bullet1[i]);
	}
	for (int i = 0; i < m_BulletIndex2; ++i)
	{
		SetBolletLifeTime(m_Bullet2[i]);
	}
}

bool CPlayScene::CircleToCircleHitCheck(NNPoint Apoint, float Aradius, NNPoint Bpoint, float Bradius)
{
	if((Aradius + Bradius) > Apoint.GetDistance(Bpoint))
	{
		return true;
	}
	return false;
}

void CPlayScene::SetPlayerMoveArea(CMaincharacter * Player)
{
	float leftline = m_Map->GetPositionX() + m_Map->GetMainFrame()->GetWidth()/2;
	float rightline = m_Map->GetPositionX() - m_Map->GetMainFrame()->GetWidth()/2;
	float botline = m_Map->GetPositionY() + m_Map->GetMainFrame()->GetHeight()/2;
	float topline = m_Map->GetPositionY() - m_Map->GetMainFrame()->GetHeight()/2;

	if (Player->GetPositionX() > leftline )
	{
		Player->SetPosition(NNPoint(leftline, Player->GetPositionY()));
	}
	if (Player->GetPositionX() < rightline)
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

void CPlayScene::SetBolletLifeTime(CBullet * Bullet)
{
	float leftline = m_Map->GetPositionX() + m_Map->GetMainFrame()->GetWidth()/2 + Bullet->GetMainCircle()->GetRadius();
	float rightline = m_Map->GetPositionX() - m_Map->GetMainFrame()->GetWidth()/2 - Bullet->GetMainCircle()->GetRadius();
	float botline = m_Map->GetPositionY() + m_Map->GetMainFrame()->GetHeight()/2 + Bullet->GetMainCircle()->GetRadius();
	float topline = m_Map->GetPositionY() - m_Map->GetMainFrame()->GetHeight()/2 - Bullet->GetMainCircle()->GetRadius();

	if (Bullet->GetPositionX() > leftline )
	{
		Bullet->SetPosition(0.f, 0.f);
	}
	if (Bullet->GetPositionX() < rightline)
	{
		Bullet->SetPosition(0.f, 0.f);
	}
	if (Bullet->GetPositionY() > botline)
	{
		Bullet->SetPosition(0.f, 0.f);
	}
	if (Bullet->GetPositionY() < topline)
	{
		Bullet->SetPosition(0.f, 0.f);
	}
}
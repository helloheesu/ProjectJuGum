#include "PlayScene.h"
#include "MainMenuScene.h"

CPlayScene::CPlayScene(void)
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
	for (int i = 0 ; i < MAX_BULLET_NUM ; ++i)
	{
		CBulletManager::GetInstance()->GetBulletArray()[i] = new CBullet;
		AddChild( CBulletManager::GetInstance()->GetBulletArray()[i] );
		CBulletManager::GetInstance()->GetBulletArray()[i]->SetVisible(false);
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
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_SPACE ) == KEY_DOWN)
	{
		CBulletManager::GetInstance()->ShotBullet(m_Player1);
	}

	//�Ѿ��� �̵�
	CBulletManager::GetInstance()->UpdateBullet(dTime);

	//ĳ������ �̵�
	m_Player1->Update(dTime);
	m_Player2->Update(dTime);

	//�ʰ� ĳ������ �浹üũ
	SetPlayerMoveArea(m_Player1);
	SetPlayerMoveArea(m_Player2);

	//�Ѿ˰� ĳ������ �浹üũ
	CBulletManager::GetInstance()->CharacterHitCheck(m_Player1);
	CBulletManager::GetInstance()->CharacterHitCheck(m_Player2);
	
	//�Ѿ��� ������Ÿ�� ó��
	CBulletManager::GetInstance()->CheckBulletLifeTime(m_Map);
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

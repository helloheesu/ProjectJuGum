#include "TestScene.h"


CTestScene::CTestScene(void)
{

	m_LogoLabelEnglish = NNLabel::Create( L"JuGums", L"Something Strange", 75.f );
	m_LogoLabelEnglish->SetColor( 255, 0, 0 );
	m_LogoLabelEnglish->SetPosition( 90.f, 30.f );
	AddChild( m_LogoLabelEnglish );

	m_LogoLabelKorean = NNLabel::Create( L"�ְ˵�", L"�ü�ü", 50.f );
	m_LogoLabelKorean->SetPosition( 170.f, 105.f );
	AddChild( m_LogoLabelKorean );

	m_PlayMenuLabel = NNLabel::Create( L"Play", L"�ü�ü", 40.f );
	m_PlayMenuLabel->SetPosition( 160.f, 320.f );
	AddChild( m_PlayMenuLabel );

	m_QuitMenuLabel = NNLabel::Create( L"Quit", L"�ü�ü", 40.f );
	m_QuitMenuLabel->SetPosition( 160.f, 420.f );
	AddChild( m_QuitMenuLabel );

	m_KeyOn = 0;
	m_MenuLabel[0] = m_PlayMenuLabel;
	m_MenuLabel[1] = m_QuitMenuLabel;
}


CTestScene::~CTestScene(void)
{
}

void CTestScene::Render()
{
	NNScene::Render();
}

void CTestScene::Update( float dTime )
{
	m_MenuLabel[m_KeyOn]->SetColor( 0, 0, 0 );
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_DOWN )
	{
		if ( m_KeyOn > 0 )
		{
			--m_KeyOn;
		}
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_DOWN )
	{
		if ( m_KeyOn < 1 )
		{
			++m_KeyOn;
		}
	}
	m_MenuLabel[m_KeyOn]->SetColor( 255, 0, 0 );
}
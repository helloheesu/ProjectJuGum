#include "ReturnScene.h"


CReturnScene::CReturnScene(void)
{
	float width = NNApplication::GetInstance()->GetScreenWidth();
	float height = NNApplication::GetInstance()->GetScreenHeight();

	m_ReturnLabel = NNLabel::Create( L"Return to Main Menu? ", L"�ü�ü", 75.f );
	m_ReturnLabel->SetPosition( width/2 - 220.f, height/4 );
	AddChild( m_ReturnLabel );

	m_YesLabel = NNLabel::Create( L"Yes", L"�ü�ü", 60.f );
	m_YesLabel->SetPosition( width/2 - 50.f, height/2 );
	AddChild( m_YesLabel );

	m_NoLabel = NNLabel::Create( L"No", L"�ü�ü", 60.f );
	m_NoLabel->SetPosition( width/2 + 200.f, height/2 );
	AddChild( m_NoLabel );

	m_bReturn = false;
	m_NoLabel->SetColor( 255, 0, 0 );
}


CReturnScene::~CReturnScene(void)
{
}

void CReturnScene::Render()
{
	NNScene::Render();
}

void CReturnScene::Update( float dTime )
{
	if ( NNInputSystem::GetInstance()->GetKeyState( VK_LEFT ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_RIGHT ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_UP ) == KEY_DOWN
		|| NNInputSystem::GetInstance()->GetKeyState( VK_DOWN ) == KEY_DOWN )
	{
		m_bReturn = !m_bReturn;

		switch (m_bReturn)
		{
		case true:
			m_NoLabel->SetColor( 0, 0, 0 );
			m_YesLabel->SetColor( 255, 0, 0 );
			break;
		case false:
			m_YesLabel->SetColor( 0, 0, 0 );
			m_NoLabel->SetColor( 255, 0, 0 );
			break;
		default:
			break;
		}
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( VK_RETURN ) == KEY_DOWN )
	{
		switch (m_bReturn)
		{
		case true:
			NNSceneDirector::GetInstance()->ChangeScene( CMainMenuScene::Create() );
			break;
		case false:
			NNSceneDirector::GetInstance()->BackToPrevScene();			
			break;
		default:
			break;
		}
	}
}

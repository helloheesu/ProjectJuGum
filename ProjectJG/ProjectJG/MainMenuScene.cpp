#include "NNConfig.h"

#include "MainMenuScene.h"
#include "NNLabel.h"
#include "NNInputSystem.h"
#include "NNAudioSystem.h"
#include "NNResourceManager.h"
#include "NNApplication.h"
#include "PlayScene.h"
#include "NNSprite.h"
#include "NNAudioSystem.h"
#include "NetSettingScene.h"

CMainMenuScene::CMainMenuScene(void)
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_BackgroundSound = NNResourceManager::GetInstance()->LoadSoundFromFile( "Sound/Space Sprinkles.mp3", true );
	NNAudioSystem::GetInstance()->Play( m_BackgroundSound );

	m_BackGround = NNSprite::Create(L"Sprite/Background.jpg");
	m_BackGround->SetPosition(NNPoint(width/2, height/2));
	m_BackGround->SetImageHeight(height);
	m_BackGround->SetImageWidth(width);
	AddChild(m_BackGround);

	m_Logo = NNSprite::Create( L"Sprite/logo.png" );
	float image_ratio = (float)width * 0.5f / m_Logo->GetImageWidth();
	m_Logo->SetImageWidth(m_Logo->GetImageWidth() * image_ratio);
	m_Logo->SetImageHeight(m_Logo->GetImageHeight() * image_ratio);
	m_Logo->SetPosition( width/2, height/4 );
	AddChild( m_Logo );

	m_MenuLabel[MENU_PLAY] = NNLabel::Create( L"Play", L"�ü�ü", 40.f );
	m_MenuLabel[MENU_PLAY]->SetColor(255.0f, 255.0f, 255.0f);
	m_MenuLabel[MENU_PLAY]->SetPosition( width/2 + 60.f, height/2 );
	AddChild( m_MenuLabel[MENU_PLAY] );

	m_MenuLabel[MENU_TEST] = NNLabel::Create( L"Test", L"�ü�ü", 40.f );
	m_MenuLabel[MENU_TEST]->SetColor(255.0f, 255.0f, 255.0f);
	m_MenuLabel[MENU_TEST]->SetPosition( width/2 + 60.f, height/2 + 80.f );
	AddChild( m_MenuLabel[MENU_TEST] );

	m_MenuLabel[MENU_QUIT] = NNLabel::Create( L"Quit", L"�ü�ü", 40.f );
	m_MenuLabel[MENU_QUIT]->SetColor(255.0f, 255.0f, 255.0f);
	m_MenuLabel[MENU_QUIT]->SetPosition( width/2 + 60.f, height/2 + 150.f );
	AddChild( m_MenuLabel[MENU_QUIT] );

	m_KeyOn = 0;
}


CMainMenuScene::~CMainMenuScene(void)
{
	NNAudioSystem::GetInstance()->Stop( m_BackgroundSound );
}

void CMainMenuScene::Render()
{
	NNScene::Render();
}

void CMainMenuScene::Update( float dTime )
{
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 255.f, 255.f);
	if ( NNInputSystem::GetInstance()->GetMainMenuInput() == UP 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == LEFT)
	{
		--m_KeyOn;
	}
	else if ( NNInputSystem::GetInstance()->GetMainMenuInput() == DOWN 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == RIGHT )
	{
		++m_KeyOn;
	}
	m_KeyOn = (m_KeyOn + MENU_LAST) % MENU_LAST;
	m_MenuLabel[m_KeyOn]->SetColor( 255.f, 0.f, 0.f );

	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
	{
		switch (m_KeyOn)
		{
		case MENU_PLAY:
			NNSceneDirector::GetInstance()->ChangeScene( new CPlayScene() );
			break;
		case MENU_TEST:
			NNSceneDirector::GetInstance()->ChangeScene(new CNetSettingScene());
			break;
		case MENU_QUIT:
			PostMessage( NNApplication::GetInstance()->GetHWND(), WM_DESTROY, 0, 0 );
			break;
		default:
			break;
		}
	}
}
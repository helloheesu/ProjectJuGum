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
#include "NNNetworkSystem.h"

CMainMenuScene::CMainMenuScene(void)
{
	NNNetworkSystem::GetInstance()->Init();

	// BGM
	m_BackgroundSound = NNResourceManager::GetInstance()->LoadSoundFromFile( MAIN_MENU_SCENE_BACKGROUND_SOUND, true );
	NNAudioSystem::GetInstance()->Play( m_BackgroundSound );

	//effectsound
	m_OkSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_OK, false );
	m_CancelSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_CANCEL, false );
	m_SelectSound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_SELECT, false );

	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	// ��� �̹���
	m_BackGround = NNSprite::Create( MAIN_MENU_SCENE_BACKGROUND_IMAGE );
	m_BackGround->SetPosition( width*0.5f, height*0.5f );
	m_BackGround->SetImageHeight(height);
	m_BackGround->SetImageWidth(width);
	AddChild(m_BackGround);

	// �޴� �� ����
	m_MenuLabel[MENU_TEST] = NNSprite::Create(MAIN_MENU_LABEL_TEST);
	AddChild( m_MenuLabel[MENU_TEST] );
	m_MenuLabel[MENU_SERVER] = NNSprite::Create(MAIN_MENU_LABEL_SERVER);
	AddChild( m_MenuLabel[MENU_SERVER] );
	m_MenuLabel[MENU_CLIENT] = NNSprite::Create(MAIN_MENU_LABEL_CLIENT);
	AddChild( m_MenuLabel[MENU_CLIENT] );
	m_MenuLabel[MENU_QUIT] = NNSprite::Create(MAIN_MENU_LABEL_QUIT);
	AddChild( m_MenuLabel[MENU_QUIT] );
	// ���� �� ����
	m_HighlightLabel[MENU_TEST] = NNSprite::Create(MAIN_MENU_HIGHLIGHT_TEST);
	AddChild(m_HighlightLabel[MENU_TEST], 1);
	m_HighlightLabel[MENU_SERVER] = NNSprite::Create(MAIN_MENU_HIGHLIGHT_SERVER);
	AddChild(m_HighlightLabel[MENU_SERVER], 1);
	m_HighlightLabel[MENU_CLIENT] = NNSprite::Create(MAIN_MENU_HIGHLIGHT_CLIENT);
	AddChild(m_HighlightLabel[MENU_CLIENT], 1);
	m_HighlightLabel[MENU_QUIT] = NNSprite::Create(MAIN_MENU_HIGHLIGHT_QUIT);
	AddChild(m_HighlightLabel[MENU_QUIT], 1);

	InitMenuLabel();

	m_KeyOn = 0;				// ���� ����Ű�� �ִ� �޴� ��ġ
	m_bMenuSelected = false;	// "�޴��� ���� ���õ��� �ʾҴ�"


	m_InstructionLabel = NNSprite::Create(MAIN_MENU_INSTRUCTION);
	m_InstructionLabel->SetPosition( width*0.5f, height*0.3f );
	AddChild(m_InstructionLabel);

	// ��Ʈ��ũ �޴� �� ����
	for (int i = 0; i < NET_MENU_NUM; i++)
	{
		m_NetMenuLabel[i] = NNLabel::Create(m_NetMenuBuffer[i], GAME_FONT, MAIN_MENU_LABEL_FONT_SIZE * 0.5f);
		AddChild(m_NetMenuLabel[i]);
	}

	InitNetworkLabel();
	
	//�ε�ȭ��
	m_Loading = NNSprite::Create( MAIN_MENU_LOADING_SCENE );
	m_Loading->SetPosition( width*0.5f, height*0.5f );
	m_Loading->SetImageHeight(height);
	m_Loading->SetImageWidth(width);
	m_Loading->SetVisible(false);
	AddChild( m_Loading );

	m_bChangeScene = false;
	m_GameMode = MODE_NONE;
	
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
	if (m_bChangeScene)
	{
		NNSceneDirector::GetInstance()->ChangeScene( new CPlayScene(m_GameMode, m_serverIP) );
		return;
	}

	// ���� ���õ� ���� ���(Ű���尡 ��ġ�� �޴�)�� ���� ������Ʈ�� �޸� ��.
	if (!m_bMenuSelected)			// ���� ���� ��尡 �������� �ʾ��� ���, Ű����(ȭ��ǥ) �Է¿� ���� �޴��� ó��.
	{
		SetUpGameMode();
	}
	else {							// ���� ��尡 ���õ��� ���, // ���� ���õ� ���� ���(Ű���尡 ��ġ�� �޴�)�� ���� ������Ʈ�� �޸� ��.
		switch (m_KeyOn)
		{
		case MENU_TEST:				// �� �ٸ� ó�� ���� ���� ����.
			ChangeScene();
		case MENU_SERVER:			// Z�� ������ ���� ����, X�� ������ �޴����� ���.
			if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE ) 
			{
				NNAudioSystem::GetInstance()->Play( m_OkSound );
				ChangeScene();
			}
			if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_TWO ) 
			{
				NNAudioSystem::GetInstance()->Play( m_CancelSound );
				CancelModeSelection();
			}
			break;
		case MENU_CLIENT:			// Z�� ������ ���� ����, X�� ������ �޴����� ���, IP�Է� ó��.
			if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE ) 
			{
				NNAudioSystem::GetInstance()->Play( m_OkSound );
				ChangeScene();
			}
			if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_TWO ) 
			{
				NNAudioSystem::GetInstance()->Play( m_CancelSound );
				CancelModeSelection();
			}
			GetIPInput();
			break;
		case MENU_QUIT:
			PostMessage( NNApplication::GetInstance()->GetHWND(), WM_DESTROY, 0, 0 );
			break;
		default:
			break;
		}
	}
}

void CMainMenuScene::SetUpGameMode()
{
	m_HighlightLabel[m_KeyOn]->SetVisible(false);
	if ( NNInputSystem::GetInstance()->GetMainMenuInput() == UP 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == LEFT)
	{
		NNAudioSystem::GetInstance()->Play( m_SelectSound );
		--m_KeyOn;
	}
	else if ( NNInputSystem::GetInstance()->GetMainMenuInput() == DOWN 
		|| NNInputSystem::GetInstance()->GetMainMenuInput() == RIGHT )
	{
		NNAudioSystem::GetInstance()->Play( m_SelectSound );
		++m_KeyOn;
	}
	m_KeyOn = (m_KeyOn + MENU_NUM) % MENU_NUM;
	m_HighlightLabel[m_KeyOn]->SetVisible(true);

	if ( NNInputSystem::GetInstance()->GetSkillKeyInput() == SKILL_KEY_ONE )
	{
		m_bMenuSelected = true;		// �޴��� ���õƴٰ� ǥ��
		NNAudioSystem::GetInstance()->Play( m_OkSound );
		// ���� ����Ű�� �ִ� �޴��� ���� �ٸ� ���� : ���Ӹ�� ����, �޴��� ���� ��� ǥ��
		switch (m_KeyOn)
		{
		case MENU_TEST:
			m_GameMode = TEST_MODE;
			break;
		case MENU_CLIENT:
			m_GameMode = CLIENT_MODE;
			ShowCommand(m_KeyOn, L"Input Server IP : ");
			break;
		case MENU_SERVER:
			m_GameMode = SERVER_MODE;
			ShowCommand(m_KeyOn, L"Your IP : ");
			GetCurrentIP();			// ������忡���� IP�ּҸ� �ٷ� ������.
			break;
		case MENU_QUIT:
			break;
		default:
			break;
		}
	}
}

void CMainMenuScene::GetCurrentIP()
{
	strcpy_s(m_serverIP, _countof(m_serverIP), NNNetworkSystem::GetInstance()->GetIpAddress());
	swprintf(m_NetMenuBuffer[NET_MENU_IP_ADDR], _countof(m_NetMenuBuffer[NET_MENU_IP_ADDR]), L"%hs", m_serverIP);
}

void CMainMenuScene::GetIPInput()
{
	size_t len = strlen(m_serverIP);
	char* buffer = new char[len+2];
	strcpy_s(buffer, len+2, m_serverIP);

	if (NNInputSystem::GetInstance()->GetKeyState(VK_OEM_PERIOD) == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('0') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('1') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('2') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('3') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('4') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('5') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('6') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('7') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('8') == KEY_DOWN ||
		NNInputSystem::GetInstance()->GetKeyState('9') == KEY_DOWN
		)
		NNAudioSystem::GetInstance()->Play( m_SelectSound );

	if ( NNInputSystem::GetInstance()->GetKeyState(VK_OEM_PERIOD) == KEY_DOWN) {buffer[len] = '.'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('0') == KEY_DOWN) {buffer[len] = '0'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('1') == KEY_DOWN) {buffer[len] = '1'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('2') == KEY_DOWN) {buffer[len] = '2'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('3') == KEY_DOWN) {buffer[len] = '3'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('4') == KEY_DOWN) {buffer[len] = '4'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('5') == KEY_DOWN) {buffer[len] = '5'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('6') == KEY_DOWN) {buffer[len] = '6'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('7') == KEY_DOWN) {buffer[len] = '7'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('8') == KEY_DOWN) {buffer[len] = '8'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState('9') == KEY_DOWN) {buffer[len] = '9'; buffer[len+1] = '\0';}
	else if ( NNInputSystem::GetInstance()->GetKeyState(VK_BACK) == KEY_DOWN) {buffer[len-1] = '\0';}

	strcpy_s(m_serverIP, _countof(m_serverIP), buffer);
	SafeDelete(buffer);
	swprintf(m_NetMenuBuffer[NET_MENU_IP_ADDR], _countof(m_NetMenuBuffer[NET_MENU_IP_ADDR]), L"%hs", m_serverIP);
}

void CMainMenuScene::ShowCommand( int MenuIndex, wchar_t* command )
{
	// �̹� �����ִ� �޴� ���� �� ĭ ������ �δ�.
	for (int i = MenuIndex+1; i < MENU_NUM; i++)
	{
		m_MenuLabel[i]->SetPosition( m_MenuLabel[i]->GetPosition() + NNPoint(MAIN_MENU_LABEL_HORIZONTAL_SPACE, 0.f) );
		m_HighlightLabel[i]->SetPosition( m_MenuLabel[i]->GetPosition() );
	}

	// IP�� �����ش� : ���� ���� �ٲٰ�, �� ��ġ �����ϰ�, �� �ٽ� ���̰� �ϰ�.
	swprintf(m_NetMenuBuffer[NET_MENU_COMMAND], _countof(m_NetMenuBuffer[NET_MENU_COMMAND]), command);
	m_NetMenuLabel[NET_MENU_COMMAND]->SetPosition( m_MenuLabel[MenuIndex]->GetPosition() + NNPoint(MAIN_MENU_LABEL_HORIZONTAL_SPACE*0.2f, 0.f) );
	m_NetMenuLabel[NET_MENU_COMMAND]->SetVisible(true);

	swprintf(m_NetMenuBuffer[NET_MENU_IP_ADDR], _countof(m_NetMenuBuffer[NET_MENU_IP_ADDR]), L"%hs", m_serverIP);
	m_NetMenuLabel[NET_MENU_IP_ADDR]->SetPosition( m_NetMenuLabel[NET_MENU_COMMAND]->GetPosition() + NNPoint(0.f, MAIN_MENU_LABEL_VERTICAL_SPACE) );
	m_NetMenuLabel[NET_MENU_IP_ADDR]->SetVisible(true);
}

void CMainMenuScene::ChangeScene()
{
	// �ε� ��
	m_Loading->SetVisible(true);
	m_bChangeScene = true;
}

void CMainMenuScene::CancelModeSelection()
{
	m_GameMode = MODE_NONE;
	m_bMenuSelected = false;

	InitMenuLabel();
	InitNetworkLabel();
}

void CMainMenuScene::InitMenuLabel()
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	m_MenuLabel[0]->SetPosition( width*0.31f, height*0.7f );
	for (int i = 1; i < MENU_NUM; i++)
	{
		m_MenuLabel[i]->SetPosition( m_MenuLabel[i-1]->GetPosition() + NNPoint(MAIN_MENU_LABEL_HORIZONTAL_SPACE, 0.f) );
	}

	for (int i = 0; i < MENU_NUM; i++)
	{
		m_HighlightLabel[i]->SetPosition(m_MenuLabel[i]->GetPosition());
		m_HighlightLabel[i]->SetVisible(false);
	}
}

void CMainMenuScene::InitNetworkLabel()
{
	for (int i = 0; i < NET_MENU_NUM; i++)
	{
		m_NetMenuLabel[i]->SetVisible(false);
	}
	strcpy_s(m_serverIP, _countof(m_serverIP), "");
}

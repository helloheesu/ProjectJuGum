#pragma once
#include "NNScene.h"
#include "GameOption.h"

class NNSprite;
class NNSpriteAtlas;
class NNSound;
class NNAnimation;

// ������ �����ϸ� ó���� ���̴� ��.

class CMainMenuScene : public NNScene
{
public:
	CMainMenuScene(void);
	virtual ~CMainMenuScene(void);

	void Render();
	void Update( float dTime );

	void SetUpGameMode();
	void ChangeScene();
	void CancelModeSelection();

	void ShowCommand(int MenuIndex, int NetMenuIndex);
	void GetIPInput(float dTime, int NetMenuIndex = NET_MENU_CLIENT);
	void GetCurrentIP(int NetMenuIndex = NET_MENU_SERVER);

	void InitMenuLabel();
	void InitNetworkLabel();

private:
	// ���
	NNSprite*		m_Loading;
	NNSprite*		m_BackGround;
	
	// �� ��ȯ�� �ѱ� parameter
	bool			m_bChangeScene;
	ENetworkMode	m_GameMode;
	char			m_serverIP[MAIN_MENU_MAX_BUFFER_SIZE];

	// �󺧵�
	NNSprite*		m_InstructionLabel;
	NNSprite*		m_MenuLabel[MENU_NUM];
	NNSprite*		m_HighlightLabel[MENU_NUM];
	unsigned int	m_KeyOn;
	bool			m_bMenuSelected;

	NNSprite*		m_NetMenuLabel[NET_MENU_NUM];
	NNSpriteAtlas*	m_AddrLabel[NET_MENU_NUM][MAIN_MENU_MAX_BUFFER_SIZE];
	NNAnimation*	m_Cursor;

	// ����
	NNSound*		m_BackgroundSound;
	NNSound*		m_OkSound;
	NNSound*		m_CancelSound;
	NNSound*		m_SelectSound;
};


#pragma once
#include "NNLabel.h"
#include "NNSprite.h"
#include "GameOption.h"

class CMaincharacter;
class NNSpriteAtlas;

// UI ������ ��� UI manager�� �Ѵ�.
// ��� UI�� �θ� UImanager �̰� Update �� Render �� ��� UImanager���� �Ѵ�.
class UImanager
{
public:
	static UImanager* GetInstance();
	static void ReleaseInstance();

	void SetAllVisible( bool visible );
	void SetFPSLabelVisible( bool visible );
	void SetPlayer1CostLabelVisible( bool visible );
	void SetPlayer2CostLabelVisible( bool visible );
	void SetPlayer1PortraitVisible( bool visible )	{ m_PlayerPortrait[RAYMU]->SetVisible( visible ); }
	void SetPlayer2PortraitVisible( bool visible )	{ m_PlayerPortrait[MARISA]->SetVisible( visible ); }

	void Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 );
	void Render();

	void SetAtlasChar(NNSpriteAtlas* atlas, char number);	// ������ �ܿ� ���ư��� �Լ� �ϵ��ڵ��̶� �ٸ� �� ���� �̤�

private:
	static UImanager* m_pInstance;
	
	UImanager(void);
	virtual ~UImanager(void);

	NNObject*	m_UIList[10];	// NNSpriteAtlas* �迭�� ���� ����.

	int			m_UINum;


	// FPS
	NNSprite*		m_FPSSprite;
	NNSpriteAtlas*	m_FPSLabel[20];
	char			m_FPSBuffer[20];

	// cost
	NNSprite*		m_PlayerPortrait[CHAR_NUM];
	NNSpriteAtlas*	m_PlayerCostLabel[CHAR_NUM][100];
	char			m_PlayerCostBuffer[CHAR_NUM][100];
		
	// ���
	NNSprite*	m_pattern;
	NNSprite*	m_time;
	NNSprite*	m_flower;
};


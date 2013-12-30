#pragma once

#include "NNSprite.h"
#include "NNSpriteAtlas.h"
#include "GameOption.h"

class CMaincharacter;
class NNSpriteAtlas;
class NNLabel;

// UI ������ ��� UI manager�� �Ѵ�.
// ��� UI�� �θ� UImanager �̰� Update �� Render �� ��� UImanager���� �Ѵ�.
class UImanager
{
public:
	static UImanager* GetInstance();
	static void ReleaseInstance();

	void SetAllVisible( bool visible );
	void SetFPSLabelVisible( bool visible ) { for(int i=0; i<20; ++i) m_FPSLabel[i]->SetVisible(visible); }
	void SetPlayer1CostLabelVisible( bool visible ) { for(int i=0; i<100; ++i) m_PlayerCostLabel[0][i]->SetVisible(visible); }
	void SetPlayer2CostLabelVisible( bool visible ) { for(int i=0; i<100; ++i) m_PlayerCostLabel[1][i]->SetVisible(visible); }
	void SetPlayer1PortraitVisible( bool visible )	{ m_PlayerPortrait[0]->SetVisible( visible ); }
	void SetPlayer2PortraitVisible( bool visible )	{ m_PlayerPortrait[1]->SetVisible( visible ); }

	void Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 );
	void Render();

	void SetAtlasChar(NNSpriteAtlas* atlas, char number);	// ������ �ܿ� ���ư��� �Լ� �ϵ��ڵ��̶� �ٸ� �� ���� �̤�

	void SetTime(float dTime) { int minute = (int)(dTime/60); int second = (int)(dTime-minute); swprintf(m_TimeBuffer, 6, L"%02d:%02d", minute, second); }
	void RotateCharPortrait() { 
		printf_s("hello\n");
		NNPoint temp = m_PlayerPortrait[0]->GetPosition();
		for (int i = 0; i < CHAR_NUM; i++) { 
			m_PlayerPortrait[i]->SetScaleX(-1);
			
			if(i+1 == CHAR_NUM) continue;
			m_PlayerPortrait[i]->SetPosition(m_PlayerPortrait[i+1]->GetPosition());
		}
		m_PlayerPortrait[CHAR_NUM-1]->SetPosition(temp);
	}

private:
	static UImanager* m_pInstance;
	
	UImanager(void);
	virtual ~UImanager(void);

	NNObject*	m_UIList[10];	// NNSpriteAtlas* �迭�� ���� ����.

	int			m_UINum;


	// FPS
	NNSprite*		m_FPSSprite;
	NNSpriteAtlas*	m_FPSLabel[UI_FPS_MAX_BUFFER_SIZE];
	char			m_FPSBuffer[UI_FPS_MAX_BUFFER_SIZE];

	// cost
	NNSprite*		m_PlayerPortrait[CHAR_NUM];
	NNSpriteAtlas*	m_PlayerCostLabel[CHAR_NUM][UI_COST_MAX_BUFFER_SIZE];
	char			m_PlayerCostBuffer[CHAR_NUM][UI_COST_MAX_BUFFER_SIZE];
		
	// ���
	NNSprite*	m_pattern;
	NNSprite*	m_time;
	wchar_t		m_TimeBuffer[6];
	NNLabel*	m_TimeLabel;
	NNSprite*	m_flower;
};


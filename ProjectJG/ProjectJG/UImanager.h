#pragma once
#include "NNLabel.h"
#include "FontNode.h"

class CMaincharacter;

// UI ������ ��� UI manager�� �Ѵ�.
// ��� UI�� �θ� UImanager �̰� Update �� Render �� ��� UImanager���� �Ѵ�.

// �ڵ帮�䰡 �� �ʿ��� �̤� �ʹ� ������ �� (������, Update ��)
class UImanager
{
public:
	static UImanager* GetInstance();
	static void ReleaseInstance();

	void SetAllVisible( bool visible );
	void SetFPSLabelVisible( bool visible ){m_FPSLabel->SetVisible(visible);m_FPSValue->SetVisible(visible);}
	void SetPlayer1CostLabelVisible( bool visible ){m_Player1CostLabel->SetVisible(visible);m_Player1CostValue->SetVisible(visible);}
	void SetPlayer2CostLabelVisible( bool visible ){m_Player2CostLabel->SetVisible(visible);m_Player2CostValue->SetVisible(visible);}

	void Update( float dTime, CMaincharacter* Player1, CMaincharacter* Player2 );
	void Render();

private:
	static UImanager* m_pInstance;
	
	UImanager(void);
	virtual ~UImanager(void);

	NNObject*	m_UIList[10];
	int			m_UINum;

	// FPS
	CFontNode*	m_FPSLabel;
	CFontNode*	m_FPSValue;

	// cost
	CFontNode*	m_Player1CostLabel;
	CFontNode*	m_Player1CostValue;
	CFontNode*	m_Player2CostLabel;
	CFontNode*	m_Player2CostValue;
};


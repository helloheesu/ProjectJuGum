#pragma once
#include "NNScene.h"
#include "GameOption.h"

class CMainMap;
class NNSprite;
class NNLabel;
class CFrame;
class CMaincharacter;

// ���� �÷��� ��. ��ġ�� ������, ���Ӱ��� ������Ʈ�� �ʿ��� ��.
class CPlayScene : public NNScene
{
public:

	CPlayScene(void);
	virtual ~CPlayScene(void);

	void Render();
	void Update( float dTime );

	bool NetworkSetMenu();
	void CountDown(float dTime);

	void EndGame();

	void CameraMove( CMaincharacter* Player, float dTime );

private:

	CMainMap*	m_MainMap;
	CFrame*		m_Frame;
	
	bool		m_netsetup;
	NNLabel*	m_MenuLabel[NET_MENU_LAST];
	unsigned int m_KeyOn;

	NNLabel* m_CountNumLabel_3;
	NNLabel* m_CountNumLabel_2;
	NNLabel* m_CountNumLabel_1;
	float m_CountNum;
	bool m_DoCount;
	
};


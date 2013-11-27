#pragma once
#include "NNScene.h"

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

	bool CircleToCircleHitCheck(NNPoint point_A, float radius_A, NNPoint point_B, float radius_B);

	bool NetworkSetMenu();

	void EndGame();

	void CameraMove( CMaincharacter* Player, float dTime );

private:

	NNSprite*	m_BackGround;

	CMainMap *	m_MainMap;
	CFrame*		m_Frame;

	float		m_CostPerSecond;
	
	bool		m_netsetup;
	NNLabel*	m_MenuLabel[NET_MENU_LAST];
	unsigned int m_KeyOn;
	
};


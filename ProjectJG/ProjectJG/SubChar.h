#pragma once
#include "GameMoveObj.h"

class CMaincharacter;
class NNAnimation;
class NNSpriteAtlas;
class NNSound;

class CSubChar :
	public CGameMoveObj
{
public:
	CSubChar(ESubCharType type_of_char);
	virtual ~CSubChar(void);

	void			Render();
	void			Update(float dTime, CMaincharacter* enemy);
	
	ESubCharState	GetState() const { return m_State; }
	void			SetState(ESubCharState val) { m_State = val; }

	void			YukariNormalAttack( float dTime );
	void			AliceNormalAttack( float dTime );

protected:
	ESubCharType	m_Type;
	ESubCharState	m_State;
	float			m_ShotTimeSum;

	NNSound*		m_Shotsound;

	NNAnimation*	m_FlyMotion;
	NNSpriteAtlas*	m_BackgroundEffect;
};

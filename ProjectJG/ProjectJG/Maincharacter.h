#pragma once
#include "GameMoveObj.h"
#include "GameOption.h"
#include "NNPoint.h"

class NNCircle;
class CMainMap;
class NNSprite;
class CFairy;
class NNAnimation;
class CPacketHandler;
class CSubChar;
class NNSound;

//�����ɸ��� ���丮���·� ����
class CMaincharacter : public CGameMoveObj
{
public:
	//����Ʈ ĳ���� Ÿ��
	CMaincharacter(ECharcterType type_of_char);
	virtual ~CMaincharacter(void);

	void			Render();
	
	void			Update(float dTime, CMaincharacter* enemy, CMainMap* map, ENetworkMode gamemode);
	void			UpdateByPeer(float dTime, CMaincharacter* enemy, CMainMap* map, ENetworkMode gamemode);

	void			UpdateMotion(float dTime);
	bool			UpdateDeadAnimation(float dTime);

	NNCircle *		GetMainCircle(){return m_Circle;}

	float			GetCost() {return m_Cost;}
	void			SetCost(float cost) {m_Cost = cost;}

	ECharcterType	GetType() {return m_Type;}

	//��ų����
	void			SkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map);
	void			SummonSubChar(float dTime, CMaincharacter* enemy);
	void			RaymuSkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map);
	void			MarisaSkillCasting(float dTime, CMaincharacter* enemy, CMainMap* map);
	void			RaymuNormalShot();
	void			RaymuFirstSkill(float dTime);
	void			MarisaNormalShot();

	void			SetHit( bool bHit ) { m_bHit = bHit; }
	bool			IsHit() { return m_bHit; }
	NNSound*		GetDeadsound() const { return m_Deadsound; }
	void			SetDeadsound(NNSound* val) { m_Deadsound = val; }

	//�������ý�ų
	void			FairySkill_1(float dTime);
	void			SummonFairy();
	void			UpdateFairy(float dTime, CMaincharacter* Enemy);

	CFairy**		GetFairyArray() { return m_pFairyArray; }
	CFairy*			GetFairy();
	void			DestroyFairy();

	void			SetSubChar(CSubChar* setsubchar){ m_SubChar = setsubchar; }

	NNSprite*		GetDeadEffect() const { return m_DeadEffect; }
	void			SetDeadEffect(NNSprite* val) { m_DeadEffect = val; }

	//��Ʈ��ũ ���� �Լ�
	CPacketHandler* GetPacketHandler() { return m_PacketHandler; }
	void			SendPacket();

protected:
	NNCircle*		m_Circle;
	ECharcterType   m_Type;
	float			m_Cost;

	NNAnimation*	m_FlyMotion;
	NNSprite*	m_DeadEffect;

	bool			m_bHit;

	CSubChar*		m_SubChar;
	CFairy*			m_pFairyArray[MAX_FAIRY_NUM];
	int				m_FairyIndex;

	NNSound*		m_Deadsound;
	NNSound*		m_Shotsound;

	float			m_DeadAnimationSumTime;
	bool			m_DoDeadSoundEffect;

	//����ȭ�� ���� �ð�
	float			m_Syntime;
	EInputSetUp		m_skill_key_input;
	EInputSetUp		m_direct_key_input;
	EInputSetUp		m_speed_key_input;

	EInputSetUp		m_StateOfDirectionKey;
	EInputSetUp		m_StateOfSpeedKey;
	EInputSetUp		m_StateOfSkillKey;

	CPacketHandler* m_PacketHandler;
};


#pragma once
#include "NNConfig.h"

class CBullet;
class CMainMap;
class CAccelBullet;
class CMaincharacter;

class CBulletManager
{
public:
	CBulletManager(void);
	virtual ~CBulletManager(void);

	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	//��ų��
	void ShotAccelBullet(CMaincharacter * Player);
	void ShotBullet(CMaincharacter * Player);
	void ShotSectorBullets(CMaincharacter* Player, int direction, int degree, int n);

	void UpdateBullet(float dTime);

	bool CharacterHitCheck(CMaincharacter * Player);
	void CheckBulletLifeTime(CMainMap * Map);
	
	//������ ������ ������� �ҷ��޴����� ����� �ҷ��� ��̷� �����ϰ� ����
	CBullet **		GetBulletArray() { return m_pBulletArray; }
	CAccelBullet ** GetAccelBulletArray() { return m_pAccelBulletArray; }
	

private:
	static CBulletManager * m_pInstance;

	CBullet *		m_pBulletArray[MAX_BULLET_NUM];
	CAccelBullet *	m_pAccelBulletArray[MAX_ACCELBULLET_NUM];
	int				m_BulletIndex;
	int				m_AccelBulletIndex;

	void			BulletLifeTime(CMainMap * Map, CBullet * Bullet);
	void			AccelBulletLifeTime(CMainMap * Map, CAccelBullet * Bullet);

	CBullet *		GetBullet();
	CAccelBullet *	GetAccelBullet();
};

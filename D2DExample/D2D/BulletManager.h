#pragma once
#include "Bullet.h"
#include "PlayScene.h"

#define MAX_BULLET_NUM 100

class CBulletManager
{
public:
	CBulletManager(void);
	virtual ~CBulletManager(void);

	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	void BulletShowerShot(CMaincharacter * Player);
	void ShotBullet(CMaincharacter * Player);
	void UpdateBullet(float dTime);
	void CharacterHitCheck(CMaincharacter * Player);
	void CheckBulletLifeTime(CMainMap * Map);
	
	//������ ������ ������� �ҷ��޴����� ����� �ҷ��� ��̷� �����ϰ� ����
	CBullet **	GetBulletArray() { return m_pBulletArray; }
	CBullet *	GetBullet();

private:
	static CBulletManager * m_pInstance;

	CBullet * m_pBulletArray[MAX_BULLET_NUM];
	int	m_BulletIndex;

	void SetBulletLifeTime(CMainMap * Map, CBullet * Bullet);
};


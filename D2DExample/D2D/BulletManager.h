#pragma once
#include "NNConfig.h"

class CBullet;
class CMainMap;
class CAccelBullet;
class CMaincharacter;
class CSatellite;
class NNObject;

class CBulletManager
{
public:
	CBulletManager(void);
	virtual ~CBulletManager(void);

	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	//��ų��
	void ShotAccelBullet(NNObject * Player);
	void ShotBullet(NNObject * Player);
	void ShotSectorNormalBullets(NNObject* Player, float direction, float degree, int n);
	void ShotSectorMixBullets(NNObject* Player, float direction, float degree, int n);
	void ShotSetupSatellite(NNObject* Player);

	void UpdateObj(float dTime);
	void UpdateBullet(float dTime);
	void UpdateSatellite(float dTime);

	bool CharacterHitCheck(CMaincharacter * Player);
	void CheckBulletLifeTime(CMainMap * Map);
	
	//������ ������ ������� �ҷ��޴����� ����� �ҷ��� ��̷� �����ϰ� ����
	CBullet **		GetBulletArray() { return m_pBulletArray; }
	CAccelBullet ** GetAccelBulletArray() { return m_pAccelBulletArray; }
	CSatellite **	GetSatelliteArray() { return m_pSatelliteArray; }
	

private:
	static CBulletManager * m_pInstance;

	CBullet *		m_pBulletArray[MAX_BULLET_NUM];
	CAccelBullet *	m_pAccelBulletArray[MAX_ACCELBULLET_NUM];
	CSatellite *	m_pSatelliteArray[MAX_SATELLITE_NUM];
	int				m_BulletIndex;
	int				m_AccelBulletIndex;
	int				m_SatelliteIndex;

	void			BulletLifeTime(CMainMap * Map, CBullet * Bullet);
	void			AccelBulletLifeTime(CMainMap * Map, CAccelBullet * Bullet);

	CBullet *		GetBullet();
	CAccelBullet *	GetAccelBullet();
	CSatellite *	GetSatellite();
};

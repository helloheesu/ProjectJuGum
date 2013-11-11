#pragma once
#include "NNConfig.h"

class CBullet;
class CMainMap;
class CAccelBullet;
class CCurveBullet;
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
	void ShotCurveBullet(NNObject * Player);
	void ShotSectorNormalBullets( NNObject* Player, float direction = 270.f, float degree = 90.f, int n = 7);
	void ShotSectorMixBullets(NNObject* Player, float direction = 270.f, float degree = 180.f, int n = 20);
	void ShotTornadoBullets(NNObject* Player, int n);
	void ShotSetupSatellite(NNObject* Player);
	void ShotSLSectorNormalBullet();

	void UpdateObj(float dTime);
	void UpdateBullet(float dTime);
	void UpdateSatellite(float dTime);

	bool CharacterHitCheck(CMaincharacter * Player);

	void CheckBulletLifeTime(CMainMap * Map);
	void CheckSatelliteLifeTime();

	void DestroyBullet(CBullet* Bullet);
	void DestroyAccelBullet(CAccelBullet* Bullet);
	void DestroyCurveBullet(CCurveBullet* Bullet);
	void DestroySatellite(CSatellite* Satellite);
	
	//������ ������ ������� �ҷ��޴����� ����� �ҷ��� ��̷� �����ϰ� ����
	CBullet **		GetBulletArray() { return m_pBulletArray; }
	CAccelBullet ** GetAccelBulletArray() { return m_pAccelBulletArray; }
	CCurveBullet**	GetCurveBulletArray() { return m_pCurveBulletArray; }
	CSatellite **	GetSatelliteArray() { return m_pSatelliteArray; }
	

private:
	static CBulletManager * m_pInstance;

	CBullet *		m_pBulletArray[MAX_BULLET_NUM];
	CAccelBullet *	m_pAccelBulletArray[MAX_ACCELBULLET_NUM];
	CCurveBullet*	m_pCurveBulletArray[MAX_CURVEBULLET_NUM];
	CSatellite *	m_pSatelliteArray[MAX_SATELLITE_NUM];
	int				m_BulletIndex;
	int				m_AccelBulletIndex;
	int				m_CurveBulletIndex;
	int				m_SatelliteIndex;

	void			BulletLifeTime(CMainMap * Map, CBullet * Bullet);
	void			AccelBulletLifeTime(CMainMap * Map, CAccelBullet * Bullet);
	void			CurveBulletLifeTime(CMainMap* Map, CCurveBullet* Bullet);

	CBullet *		GetBullet();
	CAccelBullet *	GetAccelBullet();
	CCurveBullet*	GetCurveBullet();
	CSatellite *	GetSatellite();
	
};

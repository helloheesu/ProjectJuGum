#pragma once
#include "GameOption.h"

class CBullet;
class CMainMap;
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
	void ShotBullet(NNObject * Player, EBulletType bullet_type);
	void ShotSectorNormalBullets( NNObject* Player, float direction = 270.f, float degree = 90.f, int n = 7);
	void ShotSectorMixBullets(NNObject* Player, float direction = 270.f, float degree = 180.f, int n = 20);
	void ShotTornadoBullets(NNObject* Player, int n);
	void ShotSetupSatellite(NNObject* Player);

	void ShotTBullet( NNObject* Player, float direction = 270.f, float degree =  90.f, int n = 3 );

	void ShotSLSectorNormalBullet();

	void UpdateObj(float dTime);
	void UpdateBullet(float dTime);
	void UpdateSatellite(float dTime);

	bool CharacterHitCheck(CMaincharacter * Player);

	void CheckBulletLifeTime(CMainMap * Map);
	void CheckSatelliteLifeTime();

	void DestroyBullet(CBullet* Bullet);
	void DestroySatellite(CSatellite* Satellite);
	
	//������ ������ ������� �ҷ��޴����� ����� �ҷ��� ��̷� �����ϰ� ����
	CBullet **		GetBulletArray() { return m_pBulletArray; }
	CSatellite **	GetSatelliteArray() { return m_pSatelliteArray; }
	

private:
	static CBulletManager * m_pInstance;

	// agebreak : ������ Bullet���� �θ� Ŭ������ Bullet���� �����, ��� ������ ����� �ϳ��� ����Ʈ���� ������ �� ���� ������?!
	// �̷� ������� ���߿� ���ο� Bullet Ÿ���� �߰��� �� ����, ������ �Լ����� �߰��Ǿ�� �ϴ� ������ ����.
	
	CBullet *		m_pBulletArray[MAX_BULLET_NUM];
	CSatellite *	m_pSatelliteArray[MAX_SATELLITE_NUM];
	int				m_BulletIndex;
	int				m_SatelliteIndex;

	// agebreak : �׷��� �̷� �Լ���� ������ �ξ� ����� ������ ������ ������ �� ������?
	// Bullet ��ü���� ����� �ް�, ������ Bullet Ŭ������ BulletType�� enum ������ �����Ͽ� �����ϸ� �ξ� ���� ������ �ɵ�
	void			BulletLifeTime(CMainMap * Map, CBullet * Bullet);

	CBullet *		GetBullet(EBulletType bullet_type);
	CSatellite *	GetSatellite();

};

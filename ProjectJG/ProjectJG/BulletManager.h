#pragma once
#include "GameOption.h"

class CBullet;
class CMainMap;
class CMaincharacter;
class CSatellite;
class NNObject;
class CGameMoveObj;

class CBulletManager
{
public:
	CBulletManager(void);
	virtual ~CBulletManager(void);

	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	//��ų��
	void ShotBullet(CGameMoveObj* Player, EBulletType bullet_type);
	void ShotSectorNormalBullets(CGameMoveObj* Player, float direction = 270.f, float degree = 90.f, int n = 7);
	void ShotSectorMixBullets(CGameMoveObj* Player, float direction = 270.f, float degree = 180.f, int n = 20);
	void ShotTornadoBullets(CGameMoveObj* Player, int n);
	void ShotSetupSatellite(CGameMoveObj* Player);

	void ShotTBullet( CGameMoveObj* Player, float direction = 270.f, float degree =  90.f, int n = 3 );

	void ShotSLSectorNormalBullet();

	void UpdateObj(float dTime, CMaincharacter* Enemy);
	void UpdateBullet(float dTime);
	void UpdateSatellite(float dTime , CMaincharacter* Enemy);

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

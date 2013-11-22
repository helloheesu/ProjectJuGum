#pragma once
#include "GameOption.h"

class CBullet;
class CMainMap;
class CMaincharacter;
class CSatellite;
class NNObject;
class CGameMoveObj;
class CAsteroid;

//�Ѿ˻Ӹ��ƴ϶� ���ӻ��� ��� �̵��ϴ� ������Ʈ�� ����
//������ ��ų�� ������
class CBulletManager
{
public:
	

	static CBulletManager* GetInstance();
	static void ReleaseInstance();
	
	//��ų��
	void ShotBullet(CGameMoveObj* Player, EBulletType bullet_type);
	void ShotSectorBullets(CGameMoveObj* Player, EBulletType bullet_type, float degree = 90.f, int n = 7);
	void ShotSectorMixBullets(CGameMoveObj* Player, EBulletType bullet_type_1, EBulletType bullet_type_2,float degree = 180.f, int n = 20);
	void ShotTornadoBullets(CGameMoveObj* Player, int n);
	void ShotSetupSatellite(CGameMoveObj* Player);

	//�ΰ����� ���� ��ų
	void ShotSLSectorNormalBullet();

	//����� ��ų
	void ShotAsteroid(CMainMap* Map);

	//������Ʈ
	void UpdateObj(float dTime , CMaincharacter* Enemy, CMainMap* Map);
	void UpdateBullet(float dTime, CMainMap* Map);
	void UpdateSatellite(float dTime , CMaincharacter* Enemy);
	void UpdateAsteroid(float dTime, CMainMap* Map);

	//��Ʈäũ
	bool CharacterHitCheck(CMaincharacter * Player);

	//������Ÿ��
	void DestroySatellite();
	void DestroyObj(CGameMoveObj* Obj);
	
	//������ ������ ������� �ҷ��޴����� ����� �ҷ��� ��̷� �����ϰ� ����
	CBullet**		GetBulletArray() { return m_pBulletArray; }
	CSatellite**	GetSatelliteArray() { return m_pSatelliteArray; }
	CAsteroid**		GetAsteroidArray() { return m_pAsteroidArray; }

private:
	static CBulletManager * m_pInstance;

	CBulletManager(void);
	virtual ~CBulletManager(void);
	
	CBullet*		m_pBulletArray[MAX_BULLET_NUM];
	CSatellite*		m_pSatelliteArray[MAX_SATELLITE_NUM];
	CAsteroid*		m_pAsteroidArray[MAX_ASTEROID_NUM];
	int				m_BulletIndex;
	int				m_SatelliteIndex;
	int				m_AsteroidIndex;

	void			CheckLifeTime(CMainMap * Map, CGameMoveObj * Obj);

	CBullet*		GetBullet(EBulletType bullet_type);
	CSatellite*		GetSatellite();
	CAsteroid*		GetAsteroid();

};

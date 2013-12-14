#pragma once
#include "GameOption.h"

class CBullet;
class CMainMap;
class CMaincharacter;
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
// 	void ShotBullet(CGameMoveObj* Player, EBulletType bullet_type);
// 	void ShotSectorBullets(CGameMoveObj* Player, EBulletType bullet_type, float degree = 90.f, int n = 7);
// 	void ShotSectorMixBullets(CGameMoveObj* Player, EBulletType bullet_type_1, EBulletType bullet_type_2,float degree = 180.f, int n = 20);
// 	void ShotTornadoBullets(CGameMoveObj* Player, int n);

	//źȯ�� �ʹ����� �������� Ȯ��
	void			CheckLifeTime(CMainMap * Map, CGameMoveObj * Obj);

	//�޴������Լ� źȯ�� �޾ƿ��� �Լ���
	CBullet*		GetBullet( EBulletType bullet_type, float speed, float direction );
	CAsteroid*		GetAsteroid();

	//����� ��ų
	void ShotAsteroid(CMainMap* Map);

	//������Ʈ
	void UpdateObj(float dTime , CMaincharacter* Enemy, CMainMap* Map);
	void UpdateBullet(float dTime, CMainMap* Map);
	void UpdateAsteroid(float dTime, CMainMap* Map);

	//��Ʈäũ
	bool CharacterHitCheck(CMaincharacter * Player);

	//������Ÿ��
	void DestroyObj(CGameMoveObj* Obj);
	
	//������ ������ ������� �ҷ��޴����� ����� �ҷ��� ��̷� �����ϰ� ����
	CBullet**		GetBulletArray() { return m_pBulletArray; }
	CAsteroid**		GetAsteroidArray() { return m_pAsteroidArray; }

private:
	static CBulletManager * m_pInstance;

	CBulletManager(void);
	virtual ~CBulletManager(void);
	
	CBullet*		m_pBulletArray[MAX_BULLET_NUM];
	CAsteroid*		m_pAsteroidArray[MAX_ASTEROID_NUM];
	int				m_BulletIndex;
	int				m_AsteroidIndex;

	

};

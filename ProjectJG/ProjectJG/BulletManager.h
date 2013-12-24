#pragma once
#include "GameOption.h"

class CBullet;
class CMainMap;
class CMaincharacter;
class NNObject;
class CGameMoveObj;
class CItemBox;

//�Ѿ˻Ӹ��ƴ϶� ���ӻ��� ��� �̵��ϴ� ������Ʈ�� ����
//������ ��ų�� ������
class CBulletManager
{
public:
	static CBulletManager* GetInstance();
	static void ReleaseInstance();

	//źȯ�� �ʹ����� �������� Ȯ��
	bool			CheckLifeTime(CMainMap* Map, CBullet* Obj);

	//�޴������Լ� źȯ�� �޾ƿ��� �Լ���
	CBullet*		GetBullet( EBulletType bullet_type, float speed, float direction );

	//����� ��ų
	void			ShotAsteroid(CMainMap* Map);

	//������Ʈ
	void			UpdateObj(float dTime , CMaincharacter* Enemy, CMainMap* Map);
	void			UpdateBullet(float dTime, CMainMap* Map);

	//��Ʈäũ
	bool			CharacterHitCheck(CMaincharacter * Player);

	//������Ÿ��
	void			DestroyObj(CGameMoveObj* Obj);
	void			DestroyBullet(CBullet* bullet);
	
	//������ ������ ������� �ҷ��޴����� ����� �ҷ��� ��̷� �����ϰ� ����
	CBullet**		GetBulletArray() { return m_pBulletArray; }

private:
	static CBulletManager * m_pInstance;

	CBulletManager(void);
	virtual ~CBulletManager(void);
	
	CBullet*		m_pBulletArray[MAX_BULLET_NUM];
	int				m_BulletIndex;

	int				m_BulletNum;
	float			m_TimeToCheckBulletNum;

};

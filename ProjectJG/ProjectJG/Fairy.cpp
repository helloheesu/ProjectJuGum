#include "NNConfig.h"

#include "Bullet.h"
#include "NNAnimation.h"
#include "Fairy.h"
#include "NNCircle.h"
#include "BulletManager.h"
#include "Maincharacter.h"
#include "NNSpriteAtlas.h"
#include "NNResourceManager.h"
#include "NNAudioSystem.h"

CFairy::CFairy(void) : m_ShotTimeSum(0.f), m_TimeForSummonEffect(0.f), m_DoSummonEffect(true)
{
	m_Shotsound = NNResourceManager::GetInstance()->LoadSoundFromFile( EFFECT_SOUND_SUBCHAR_SHOT, false );

	m_FairyMotion = NNAnimation::Create( 5, 0.2f,	
		L"Sprite/fairy1.png",
		L"Sprite/fairy2.png",
		L"Sprite/fairy3.png",
		L"Sprite/fairy4.png",
		L"Sprite/fairy5.png");

	AddChild( m_FairyMotion );
}

CFairy::~CFairy(void)
{
}

void CFairy::Render()
{
	NNObject::Render();
}

void CFairy::Update( float dTime, CMaincharacter* Enemy)
{
	if (m_DoSummonEffect)
		SummonFairyEffect(dTime);

	UpdateShotDirection(Enemy);
	UpdateShotPoint(SHOT_POINT);

	NormalAttack(dTime);

	m_FairyMotion->Update(dTime);
	m_FairyMotion->SetRotation(GetShotDirection() + 90.f);
}

void CFairy::NormalAttack( float dTime )
{	
	m_ShotTimeSum += dTime;
	if (m_ShotTimeSum >= 2.f)
	{
		//NNAudioSystem::GetInstance()->Play( m_Shotsound );

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(FAIRY_NORMAL_BULLET, FAIRY_NORMAL_BULLET_SPEED, GetShotDirection());
		pBullet->SetDirection(GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		m_ShotTimeSum = 0.f;
	}
}

void CFairy::SectorAttack( float dTime )
{
	float degree = 120.f;
	int n = 6;

	for (int i = 0; i < n; ++i)
	{
		float direction = GetShotDirection() - degree*0.5f + degree/(n-1)*i;

		CBullet* pBullet = CBulletManager::GetInstance()->GetBullet(FAIRY_NORMAL_BULLET, 0, GetShotDirection());
		pBullet->SetPosition(GetShotPoint());
		pBullet->SetDirection(direction);
		pBullet->GetTexture(FAIRY_NORMAL_BULLET)->SetRotation(direction + 90.f);
	}
	m_ShotTimeSum = 0.f;
}

void CFairy::SummonFairyEffect( float dTime )
{
	m_TimeForSummonEffect += dTime;

	if (m_TimeForSummonEffect < 0.1)
	{
		m_FairyMotion->SetOpacity(m_TimeForSummonEffect*10.f);
		m_FairyMotion->SetScaleX(3.0f - 20.f*m_TimeForSummonEffect);
	}
	else
		m_DoSummonEffect = false;
}




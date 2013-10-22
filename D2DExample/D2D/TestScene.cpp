#include "TestScene.h"


CTestScene::CTestScene(void)
{
	m_DifferentFontLabel = NNLabel::Create( L"JuGums", L"�ü�ü", 75.f );
	m_DifferentFontLabel->SetPosition( 90.f, 30.f );
	AddChild( m_DifferentFontLabel );

	m_DifferentFontLabel = NNLabel::Create( L"�ְ˵�", L"�ü�ü", 50.f );
	m_DifferentFontLabel->SetPosition( 170.f, 105.f );
	AddChild( m_DifferentFontLabel );

	m_DifferentFontLabel = NNLabel::Create( L"Play", L"�ü�ü", 40.f );
	m_DifferentFontLabel->SetPosition( 160.f, 320.f );
	AddChild( m_DifferentFontLabel );

	m_DifferentFontLabel = NNLabel::Create( L"Quit", L"�ü�ü", 40.f );
	m_DifferentFontLabel->SetPosition( 160.f, 420.f );
	AddChild( m_DifferentFontLabel );
}


CTestScene::~CTestScene(void)
{
}

void CTestScene::Render()
{
	NNObject::Render();
}

void CTestScene::Update( float dTime )
{
}
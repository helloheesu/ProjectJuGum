
#pragma once

#include "NNScene.h"
#include "NNConfig.h"

/* */
/* NNSceneDirector
/* ������ ���� �����ϴ� �̱��� Ŭ����
/* ��ϵ� ���� ���, ó���ϴ� ��Ȱ�̴�.
/* */

class NNSceneDirector
{

public:
	static NNSceneDirector* GetInstance();
	static void ReleaseInstance();

public:
	bool Init();
	bool Release();

public:
	bool ChangeScene( NNScene* scene );
	bool RenderScene();
	bool UpdateScene( float dTime );


private:
	static NNSceneDirector* m_pInstance;

private:
	NNSceneDirector();
	~NNSceneDirector();


private:
	NNScene* m_NowScene;

};



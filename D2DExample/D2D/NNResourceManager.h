
#pragma once

#include "NNConfig.h"
#include "NNTexture.h"

/* */
/* NNResourceManager
/* ���� ���ҽ��� �����ϴ� �̱��� Ŭ����
/* ���� �ؽ��� ���ϸ� ������
/* */

class NNResourceManager
{

public:
	static NNResourceManager* GetInstance();
	static void ReleaseInstance();

	//NNTexture* LoadTexture( std::string key );
	NNTexture* LoadTextureFromFile( std::wstring path );


private:
	static NNResourceManager* m_pInstance;

private:
	std::map<std::wstring,NNTexture*> m_TextureTable;

private:
	NNResourceManager();
	~NNResourceManager();
};



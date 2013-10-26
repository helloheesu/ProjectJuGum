
#include "NNApplication.h"
#include "NNAudioSystem.h"

#include "SpriteExample.h"
#include "LabelExample.h"
#include "SoundExample.h"
#include "InputExample.h"
#include "CustomObjectExample.h"
#include "MainMenuScene.h"
#include "PlayScene.h"
#include "ReturnScene.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nShowCmd )
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( );

	AllocConsole();
	FILE* pStream;
	freopen_s( &pStream, "CONOUT$", "wt", stdout );
#endif


	NNApplication* Application = NNApplication::GetInstance();

	Application->Init( L"JuGums", 1000, 700, D2D );

	// Sprite Example
	// NNSceneDirector::GetInstance()->ChangeScene( SpriteExample::Create() );

	// Label Example
	// NNSceneDirector::GetInstance()->ChangeScene( LabelExample::Create() );

	// Input Example
	// NNSceneDirector::GetInstance()->ChangeScene( InputExample::Create() );

	// Sound Example
	// NNSceneDirector::GetInstance()->ChangeScene( SoundExample::Create() );

	// CustomObject Example
	// NNSceneDirector::GetInstance()->ChangeScene( CustomObjectExample::Create() );

	// TestMenuScene
	 NNSceneDirector::GetInstance()->ChangeScene( CMainMenuScene::Create() );

	// Playtest
	// NNSceneDirector::GetInstance()->ChangeScene( CPlaytest::Create() );

	// ReturnScene
	// NNSceneDirector::GetInstance()->ChangeScene( CReturnScene::Create() );

	Application->Run();
	Application->Release();

	// for debugging
	FreeConsole();

	return 0;
}
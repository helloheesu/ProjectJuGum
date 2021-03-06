#include "NNConfig.h"

#include "NNApplication.h"
#include "NNAudioSystem.h"

#include "MainMenuScene.h"
#include "PlayScene.h"
#include "ReturnScene.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nShowCmd )
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( );

#endif

	srand((unsigned int)time(NULL));

	NNApplication* Application = NNApplication::GetInstance();


#ifdef _DEBUG
	Application->Init( L"JuGums", WINDOW_WIDTH, WINDOW_HEIGHT, D2D, false);
#else
	Application->Init( L"JuGums", WINDOW_WIDTH, WINDOW_HEIGHT, D2D, true);
#endif // _DEBUG
	
	NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );

	Application->Run();
	Application->Release();

	return 0;
}
#include "GameManager.h"


GameManager* GameManager::mInstance = NULL;
GameManager::GameManager()
{
	mCurrentScene = nullptr;
}


GameManager* GameManager::GetInstance()
{
	if (!mInstance)
		mInstance = new GameManager();

	return mInstance;
}

GameManager::~GameManager()
{
}

Game* GameManager::GetCurrentScene()
{
	return mCurrentScene;
}

void GameManager::Update(HWND hWnd, int dt)
{
	mCurrentScene->Game_Run(hWnd, dt);
}

void GameManager::ReplaceScene(Game* scene)
{
	//delete mCurrentScene;
	mCurrentScene = scene;
	//initialize the game
	if (!mCurrentScene->Game_Init(hwnd))
	{
		MessageBox(hwnd, "Error initializing the game", "Error", MB_OK);

	}

}

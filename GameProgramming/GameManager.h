#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__
//new 02-11, zPhong
#include "game.h"


class GameManager
{
public:
	static GameManager *GetInstance();
	~GameManager();

	Game* GetCurrentScene();
	void Update(HWND, int);
	void ReplaceScene(Game *scene);

private:
	GameManager();
	static GameManager *mInstance;
	Game *mCurrentScene;
};

#endif
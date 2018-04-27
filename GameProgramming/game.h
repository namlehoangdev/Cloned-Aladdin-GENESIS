#ifndef _GAME_H
#define _GAME_H
#include <d3d9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxgraphics.h"
#include "dxaudio.h"
#include "sprite.h"
#include "AABB.h"
#include "GameObject.h"
#include <list>
#include "Quadtree.h"
#include "GameObjectMove.h"
#include "UIScene.h"


//application title
#define APPTITLE "FrameworkStage"
//screen setup
#define FULLSCREEN 0
#define SCREEN_WIDTH 660
#define SCREEN_HEIGHT 480
//macros to read the keyboard asynchronously
#define KEY_PRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) 
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define FIXED_TIME 1
//function prototypes
//GamePlay
enum GAMECASES
{
	CONTINUE,
	QUIT,
	PLAYING,
	CHOSING,

	COMPLETE,
	WIN,
	END
};
class Game
{
protected:

	//2312
	GAMECASES gameCase;
	GameObject *Abu = new GameObject();
	LPDIRECT3DSURFACE9 wishBackground;
	LPDIRECT3DSURFACE9 completeBackground;
	LPDIRECT3DSURFACE9 winBackground;
	LPDIRECT3DSURFACE9 endBackground;


	RECT viewRect;
	CSound* _soundTheme;
	CSound* _soundComplete;

	D3DXIMAGE_INFO* mapinfo;
	UIScene* _UI;
	RECT animateBackground;
	int index = 0;
	int speed = 8;

public:
	UIScene* ui() const
	{
		return _UI;
	}

	void set_ui(UIScene* ui_scene)
	{
		_UI = ui_scene;
	}

protected:
	map<string, int> mapIdName;

public:
	D3DXIMAGE_INFO* MapInfo() const
	{
		return mapinfo;
	}

	void set_mapinfo(D3DXIMAGE_INFO* mapinfo)
	{
		this->mapinfo = mapinfo;
	}

protected:
	list<GameObjectMove*>* _healthHavingList;
	list<GameObject*>* _gameObjectList;
	list<GameObject*>* _onScreenList;
	list<GameObject*>*_itemsList;

public:
	list<GameObject*>* ItemsList() const
	{
		return _itemsList;
	}

	void set_health_having_list(list<GameObject*>* listItems)
	{
		_itemsList = listItems;
	}

	list<GameObjectMove*>* health_having_list() const
	{
		return _healthHavingList;
	}

	void set_health_having_list(list<GameObjectMove*>* game_object_moves)
	{
		_healthHavingList = game_object_moves;
	}

	list<GameObject*>* on_screen_list() const
	{
		return _onScreenList;
	}

	void set_on_screen_list(list<GameObject*>* game_objects)
	{
		_onScreenList = game_objects;
	}

	list<GameObject*>* disposable_list() const
	{
		return _disposableList;
	}

	void set_disposable_list(list<GameObject*>* game_objects)
	{
		_disposableList = game_objects;
	}

protected:
	list<GameObject*>* _disposableList;
public:
	list<GameObject*>* game_object_list() const
	{
		return _gameObjectList;
	}

	void set_game_object_list(list<GameObject*>* game_objects)
	{
		_gameObjectList = game_objects;
	}
	//void LoadListObjectXml(char* xmlpath);
protected:

	void ProcessKeyboard(); //for making action by pressing (not hold) button, a part of input update

	virtual list<GameObject*>* OnScreenDetect();
	
	virtual void DisposablePhysicUpdate(float);
	virtual void CollisionDetect();
	virtual void Key_Pressed(int KeyCode);
	virtual void InputUpdate();
	virtual void PhysicsUpdate(float);
	virtual void GraphicUpdate(float t);
public:
	Game();
	virtual ~Game();
	int virtual Game_Init(HWND);
	void virtual Game_Run(HWND, int);
	void virtual Game_End(HWND);

	static int NUMBER_OF_SCENES_CREATED;
	static int NUMBER_OF_SCENES_DELETED;
	
};
#endif
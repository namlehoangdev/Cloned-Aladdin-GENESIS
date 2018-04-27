#pragma once
#include "GameManager.h"
#include "Aladdin.h"
#include "StarBullet.h"

class Scene2: public Game
{
private:
	//sound
	CSound* _soundJump;
	CSound* _soundSlash;
	CSound* _soundThrowApple;
	CSound* _soundCollectApple;
	CSound* _soundAppleCollision;
	CSound* _soundWin;

	//object
	GameObjectMove* _Jafar;
	Aladdin* _mainCharacter;
	CSound* _soundAnaconda;
	list<GameObject*>* _enemyBulletFireList;
	list<StarBullet*>* _enemyBulletStarList;
	LPDIRECT3DSURFACE9 background;
	LPDIRECT3DTEXTURE9 mapETC;
	virtual void DisposablePhysicUpdate(float) override;
	virtual void CollisionDetect() override;
	void NormalizeAction();
	virtual void Key_Pressed(int KeyCode) override;
	virtual void InputUpdate() override;
	void JafarAI(GameObjectMove* jafar);
	virtual void PhysicsUpdate(float) override;
	virtual void GraphicUpdate(float t) override;
	virtual list<GameObject*>* OnScreenDetect() override;
public:
	int Game_Init(HWND) override;
	void Game_Run(HWND, int) override;
	void LoadListObjectXml(char* xmlpath);
	void Game_End(HWND) override;

	Scene2();
	~Scene2();
};


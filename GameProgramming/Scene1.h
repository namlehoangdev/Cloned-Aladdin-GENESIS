#pragma once
#ifndef _SCENE1_H
#define _SCENE1_H
#include"Aladdin.h"
#include "game.h"
#include <list>
#include <d3dx9.h>
#include "UIScene.h"
#include "Scene1BackGround.h"

class Scene1: public Game
{
private: 

	//Disappear effect
	GameObject* _explosion;
	//Special object in scene
	GameObjectMove* _camel;
	Aladdin* mainCharacter;
	CSound* _soundJump;
	CSound* _soundSlash;
	CSound* _soundThrowApple;
	CSound* _soundCollectApple;
	CSound* _soundCamel;
	CSound* _soundSpringBoard;
	CSound* _soundAppleCollision;
	CSound* _soundPotFall;
	CSound* _soundTaunt;
	CSound* _soundFire;
	CSound* _soundThrow;
	CSound* _soundWow;

	CSound* _soundGem;
	CSound* _soundHighSword;
	CSound* _soundLowSword;
	CSound* _soundPush;
	CSound* _soundPantDrop;
	CSound* _soundHitted;



	Scene1BackGround* background;
	LPDIRECT3DTEXTURE9 mapETC;
	//GameObject * testObject = new GameObject();//object duoi dang co xml
	//GameObject * namObject = new GameObject();//object duoi dang chi co mot hinh anh
private:
	D3DXVECTOR3 hittedPosition = D3DXVECTOR3(0,0,0);
	
	virtual void DisposablePhysicUpdate(float) override;
	void EnemyThinAI(GameObjectMove* obj_mov);
	void EnemyMusAI(GameObjectMove* obj_mov);
	void EnemyFatAI(GameObjectMove* obj_mov);
	void EnemyJugAI(GameObjectMove* obj_mov);
	void EnemyJarAI(GameObjectMove* obj_mov);
	void EnemyHandAI(GameObjectMove* obj_mov);
	virtual void CollisionDetect() override;
	virtual void Key_Pressed(int KeyCode) override;
	void NormalizeAction();
	virtual void InputUpdate() override;
	virtual void PhysicsUpdate(float) override;
	virtual void GraphicUpdate(float t) override;
	void EnemyHandle(float t);
	void LoadListObjectXml(char *xmlpath) ;
public:
	int Game_Init(HWND) override;
	void Game_End(HWND) override;
	void Game_Run(HWND, int) override;
	Scene1();
	~Scene1();
};
#endif


#pragma once
#ifndef _SCENEHOME_H
#define _SCENEHOME_H
#include"Aladdin.h"
#include "game.h"
#include <list>
#include <d3dx9.h>

class SceneHome : public Game
{
private:
	//Aladdin* mainCharacter;
	DWORD start; 
	LPDIRECT3DSURFACE9 background;
	GameObject * knifePointer = new GameObject();  

 
	virtual void Key_Pressed(int KeyCode) override;
	virtual void InputUpdate() override;
	virtual void PhysicsUpdate(float) override;
	virtual void GraphicUpdate(float t) override;
	 
public:
	int Game_Init(HWND) override;
	void Game_Run(HWND, int) override;
	void Game_End(HWND) override;
	SceneHome();
	~SceneHome();
};
#endif


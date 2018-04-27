#pragma once
#include "sprite.h"
#include "AbuFacePrefab.h"


class Scene1BackGround
{
private:
	Sprite* _sprite;
	int _index[4],_maxindex[4];
	RECT _rect[5];
	int _speed[4] = { 2,5,6,10 };
	D3DXVECTOR3 _position[5];
	D3DXMATRIX backgroundMatrix;


public:
	void LoadRectByXML();
	void Render();
	void Update();
	Scene1BackGround();
	~Scene1BackGround();
};


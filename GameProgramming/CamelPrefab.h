#pragma once

#include "GameObjectMove.h";

class CamelPrefab
{
public:
	static void Instantiate(GameObjectMove*,float,float, int, int);
	static void BeBeaten(GameObject* gameObject);
	CamelPrefab();
	~CamelPrefab();
};


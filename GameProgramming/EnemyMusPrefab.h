#pragma once
#include "GameObjectMove.h";

class EnemyMusPrefab
{
public:
	static void Instantiate(GameObjectMove*, float, float, int, int, int, int);

	EnemyMusPrefab();
	~EnemyMusPrefab();
};


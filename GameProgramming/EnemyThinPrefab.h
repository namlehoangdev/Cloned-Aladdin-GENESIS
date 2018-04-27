#pragma once
#include "GameObjectMove.h";

class EnemyThinPrefab
{
public:
	static void Instantiate(GameObjectMove*, float, float, int, int, int, int);

	EnemyThinPrefab();
	~EnemyThinPrefab();
};


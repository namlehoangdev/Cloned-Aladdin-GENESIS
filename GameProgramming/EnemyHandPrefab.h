#pragma once
#include "GameObjectMove.h";

class EnemyHandPrefab
{
public:
	static void Instantiate(GameObjectMove*, float, float, int, int, int, int);

	EnemyHandPrefab();
	~EnemyHandPrefab();
};


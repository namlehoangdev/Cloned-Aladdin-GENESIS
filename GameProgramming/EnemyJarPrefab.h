#pragma once
#include "GameObjectMove.h";

class EnemyJarPrefab
{
public:
	static void Instantiate(GameObjectMove*, float, float, int, int, int, int);

	EnemyJarPrefab();
	~EnemyJarPrefab();
};


#pragma once
#include "GameObjectMove.h";

class EnemyFatPrefab
{
public:
	static void Instantiate(GameObjectMove*,float ,float, int, int,int ,int);
	EnemyFatPrefab();
	~EnemyFatPrefab();
};


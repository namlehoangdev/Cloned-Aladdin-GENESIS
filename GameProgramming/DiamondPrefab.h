#pragma once
#include "GameObject.h";


class DiamondPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	DiamondPrefab();
	~DiamondPrefab();
};


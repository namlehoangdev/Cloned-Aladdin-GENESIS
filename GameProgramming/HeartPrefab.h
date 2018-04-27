#pragma once
#include "GameObject.h";


class HeartPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	HeartPrefab();
	~HeartPrefab();
};


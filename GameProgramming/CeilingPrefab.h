#pragma once
#include "GameObject.h"
class CeilingPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	CeilingPrefab();
	~CeilingPrefab();
};


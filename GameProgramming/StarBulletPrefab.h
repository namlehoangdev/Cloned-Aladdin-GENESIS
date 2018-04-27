#pragma once
#include "GameObject.h"

class StarBulletPrefab
{
public:
	static void Instantiate(GameObject*, int, int, GameObject::Face);
	StarBulletPrefab();
	~StarBulletPrefab();
};


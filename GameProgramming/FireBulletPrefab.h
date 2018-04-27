#pragma once
#include "GameObject.h"
class FireBulletPrefab
{
public:
	static void Instantiate(GameObject*, int, int, GameObject::Face);
	FireBulletPrefab();
	~FireBulletPrefab();
};


#pragma once
#include <string>
#include "GameObject.h"
class GameObject;
#define BULLET_PREFAB_VX 4
namespace BulletPrefab
{
	void Instantiate(GameObject*, char*, int, int, GameObject::Face);
}


#pragma once
class GameObject;

class WallPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	WallPrefab();
	~WallPrefab();
};


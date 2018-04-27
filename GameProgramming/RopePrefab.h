#pragma once
class GameObject;

class RopePrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	RopePrefab();
	~RopePrefab();
};


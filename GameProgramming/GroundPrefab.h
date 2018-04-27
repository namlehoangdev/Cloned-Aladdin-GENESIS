#pragma once
class GameObject;

class GroundPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	GroundPrefab();
	~GroundPrefab();
};


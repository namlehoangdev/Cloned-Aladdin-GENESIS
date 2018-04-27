#pragma once
class GameObject;

class StairsPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	StairsPrefab();
	~StairsPrefab();
};


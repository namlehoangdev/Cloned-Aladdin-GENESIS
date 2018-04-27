#pragma once
class GameObject; 
class AbuPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	AbuPrefab();
	~AbuPrefab();
};

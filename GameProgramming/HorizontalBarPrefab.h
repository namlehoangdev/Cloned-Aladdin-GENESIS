#pragma once
class GameObject;

class HorizontalBarPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	HorizontalBarPrefab();
	~HorizontalBarPrefab();
};


#pragma once
class GameObject;

class FloatGroundPrefab
{
public:
	static void Instantiate(GameObject*,float,float, int, int);
	FloatGroundPrefab();
	~FloatGroundPrefab();
};


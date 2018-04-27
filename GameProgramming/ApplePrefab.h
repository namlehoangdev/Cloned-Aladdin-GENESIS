#pragma once
class GameObject;

class ApplePrefab
{
public:
	static void Instantiate(GameObject*,float,float, int, int);
	ApplePrefab();
	~ApplePrefab();
};


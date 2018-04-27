#pragma once
class GameObject;

class TriggerPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	TriggerPrefab();
	~TriggerPrefab();
};


#pragma once
class GameObject;

class SpringBoardPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);
	SpringBoardPrefab();
	~SpringBoardPrefab();
};


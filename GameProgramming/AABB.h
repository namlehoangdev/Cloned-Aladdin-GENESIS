#pragma once
//new 02-11 chipu
#ifndef _AABB_H
#define _AABB_H
#include"GameObject.h"
enum Side
{
	LEFT,
	RIGHT,
	UPTOP,
	DOWNBOTTOM,
	NONE
};
struct CollisionResult
{
	float _collisionIndex;
	Side _collisionSide;
};
//RECT CalculateBoundingBox(int, int, int, int);
RECT CalculateBoundingBox(float x, float y, int width, int height, AnchorPoint anchor);
RECT GetSweptBroadphaseRect(const RECT&);

bool SimpleIntersect(RECT* rect1, RECT* rect2);
CollisionResult CheckCollision(GameObject*, GameObject*); //moving vs static
class CollisionPair
{
private:
	CollisionResult _collisionResult;
public:
	CollisionResult collisionResult() const
	{
		return _collisionResult;
	}

	void setCollisionResult(const CollisionResult& collisionResult)
	{
		_collisionResult = collisionResult;
	}

private:
	GameObject* _obj1, *_obj2;

public:
	GameObject* obj1() const
	{
		return _obj1;
	}

	void set_obj1(GameObject* game_object)
	{
		_obj1 = game_object;
	}

	GameObject* obj2() const
	{
		return _obj2;
	}

	void set_obj2(GameObject* game_object)
	{
		_obj2 = game_object;
	}

	CollisionPair(GameObject*, GameObject*);
	~CollisionPair();
	static bool IsIndentical(CollisionPair* cp1, CollisionPair* cp2);



};
float CalculateY(float, float, float, float);
int CalculateParabolVy(int vx, D3DXVECTOR3 startposition, int max_x, int max_y, float curPosX);


#endif

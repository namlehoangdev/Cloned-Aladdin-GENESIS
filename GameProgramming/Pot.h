#pragma once
#include "GameObject.h"
class Pot: public GameObject
{
	int _breakPoint;
public:
	int break_point() const
	{
		return _breakPoint;
	}

	void set_break_point(int break_point)
	{
		_breakPoint = break_point;
	}
	Pot();
	~Pot();
};


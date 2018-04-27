#pragma once
#include "GameObject.h"
class StarBullet: public GameObject
{
	D3DXVECTOR3 _targetPosition;
public:
	D3DXVECTOR3 target_position() const
	{
		return _targetPosition;
	}

	void set_target_position(const D3DXVECTOR3& d3_dxvector3)
	{
		_targetPosition = d3_dxvector3;
	}

	bool reach_target() const
	{
		return _reachTarget;
	}

	void set_reach_target(bool reach_target)
	{
		_reachTarget = reach_target;
	}

private:
	bool _reachTarget;
public:
	StarBullet();
	~StarBullet();
};


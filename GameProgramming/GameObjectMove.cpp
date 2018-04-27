#include "GameObjectMove.h"
#include "trace.h"
#include "Camera.h"
#include "GameManager.h"
#define STOP_TRACKING_DISTANCE 10

int GameObjectMove::NUMBER_GOMOVE_CREATED = 0;
int GameObjectMove::NUMBER_GOMOVE_DELETED = 0;

GameObjectMove::GameObjectMove()
{
	GameObject::GameObject();
	_isThrowing = false;
	_isImmune = 0.0f;
	_health = 0;
	_vx = 0;
	//_weaponObj = new GameObject();
	NUMBER_GOMOVE_CREATED++;
}

void GameObjectMove::GraphicUpdate(float t)
{
	GameObject::GraphicUpdate(t);
}

void GameObjectMove::PhysicUpdate(float t)
{
	int temp_x = x() + _vx*t;
	if (temp_x > min_x() && temp_x < max_x())
		_reachLimit = false;
	else _reachLimit = true;
	if (distance_from_main()>= STOP_TRACKING_DISTANCE && _reachLimit==false)
	{

		setPosition(temp_x, y() + _vy*t);
		_isStandStill = false;
	}
		

	if (hand_state() != "1")
	{
		_isStandStill = false;
	}	
	else
	{
		_isStandStill = true;
	}
		
	
	if (_isImmune != 0.0f)
		_isImmune--;
	if (_handState == "2" && _stateManager->life_span() == 3)
	{
		CalSword();
	}
	if (_handState == "2" && _stateManager->life_span() <= 1)
	{
		_handState = "0";
		DelSword();
	}
	
}

void GameObjectMove::CalSword()
{
	if (_sword!= nullptr)
	{
		if (main_state() == "2")
		{
			_sword = &getBoundingBox(main_state() + sub_state() + "2");
			return;
		}
		_sword->top = _boundingBox.top;
		_sword->bottom = _boundingBox.bottom;
		if (curface() == Face::RIGHT)
		{
			_sword->left = _boundingBox.right;
			_sword->right = _sword->left + 35;
			return;
		}
		else
		{
			_sword->right = _boundingBox.left;
			_sword->left = _sword->right - 35;
			return;
		}
	}
	

}

void GameObjectMove::DelSword()
{
	if (_sword!=nullptr)
	{
		_sword->bottom = 0;
		_sword->top = 0;
		_sword->right = 0;
		_sword->left = 0;
	}

}

GameObjectMove::~GameObjectMove()
{
	NUMBER_GOMOVE_DELETED++;
	delete _sword;

}

int GameObjectMove::health()
{
	return _health;
}

void GameObjectMove::set_health(int newHealth)
{
	_health = newHealth;
}

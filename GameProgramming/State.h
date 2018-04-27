#pragma once
#include <string>
#include <Windows.h>
#include "pugixml.hpp"
#include <vector>
using namespace pugi;

class State
{
private:
	std::vector<RECT> _srcRect;
	std::string _name;
	RECT _maxBounding;
	RECT _minBounding;
	RECT _averageBounding;
	int _animaDelay;

public:
	State();
	~State();
	State(std::string stateName,std::vector<RECT> rect,const int &animaDelay);
	const std::vector<RECT>& getListRect() const;
	std::string	getName() const;

	int AnimaDelay()
	{
		return _animaDelay;
	}

	void set_animaDelay(const int &newAnimaDelay)
	{
		_animaDelay = newAnimaDelay;
	}
	RECT MaxBounding()const
	{
		return _maxBounding;
	}
	RECT MinBounding() const
	{
		return _minBounding;
	}
	RECT AverageBounding() const
	{
		return _averageBounding;
	}


};
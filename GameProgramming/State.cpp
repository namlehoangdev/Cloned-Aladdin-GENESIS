#include "State.h"



State::State()
{ 
	_name = "";
	_animaDelay = 1;

}


State::~State()
{
	_srcRect.clear();
}
State::State(const std::string stateName, const std::vector<RECT> rect,const int& animaDelay)
{
	_name = stateName;
	_srcRect = rect;
	_animaDelay = animaDelay;
	if (!_srcRect.empty())
	{
		_maxBounding.top = _minBounding.top = _srcRect[0].top;
		_maxBounding.bottom = _minBounding.bottom = _srcRect[0].bottom;
		_maxBounding.left = _minBounding.left = _srcRect[0].left;
		_maxBounding.right = _minBounding.right = _srcRect[0].right;
		for (RECT rect : _srcRect)
		{
			if (rect.bottom - rect.top >_maxBounding.bottom - _maxBounding.top)
			{
				_maxBounding.top = _minBounding.top = rect.top;
				_maxBounding.bottom = _minBounding.bottom = rect.bottom;
			}
			if (rect.right - rect.left > _maxBounding.right - _maxBounding.left)
			{
				_maxBounding.left = _minBounding.left = rect.left;
				_maxBounding.right = _minBounding.right = rect.right;
			}

			if (rect.bottom - rect.top <_minBounding.bottom - _minBounding.top)
			{
				_minBounding.top = _minBounding.top = rect.top;
				_minBounding.bottom = _minBounding.bottom = rect.bottom;
			}
			if (rect.right - rect.left < _minBounding.right - _minBounding.left)
			{
				_minBounding.left = _minBounding.left = rect.left;
				_minBounding.right = _minBounding.right = rect.right;
			}
		}
		_averageBounding.top = (_maxBounding.top + _minBounding.top) / 2;
		_averageBounding.bottom = (_maxBounding.bottom + _minBounding.bottom) / 2;
		_averageBounding.left = (_maxBounding.left + _minBounding.left) / 2;
		_averageBounding.right = (_maxBounding.right + _minBounding.right) / 2;
	}
}


const std::vector<RECT>& State::getListRect() const
{
	return _srcRect;
}


std::string State::getName() const
{
	return _name;
}
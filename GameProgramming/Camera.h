#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
//06-11 zPhong

#include "d3d9.h"
#include "d3dx9.h"
#include <list>

class MyCamera : public GameObject
{
private:
	RECT _viewRect;
	static MyCamera* _instance;
	long _curMapWidth, _curMapHeight;

	D3DXVECTOR2 _positionCharacter;
	RECT	    _boundingCharacter;

	//attributes for update up-down camera
	int _vyTranslate;
	int _distanceUpDown;
	int _distanceLeftRight;

	//attributes for update left-right camera
	int _vxTranslate;
	int _maxLookLeft;
	int _maxLookRight;
	int _specialState;
	bool _isUpdateLeftRight;
	bool _isAbsorbed=false;


	//for character
	bool _isCharacterDying;

public:
	MyCamera();
	~MyCamera();
	static MyCamera* GetInstance();

	RECT ExtraView();
	void RenderBounding(D3DCOLOR color = D3DCOLOR_ARGB(0, 255, 255, 255), bool isRotation = false, bool isScale = false, bool isTranslation = true) override;
	void Update(float t);

	//method to update left-right position
	void LookLeft(const float &t, const bool &toNormal);
	void LookRight(const float &t, const bool &toNormal);
	void LeftRightToNormal(const float &t);
	void UpdateLeftRight(const float &t);

	//method to update up-down position
	void LookUp(const float &t, const bool &toNormal);
	void LookDown(const float &t, const bool &toNormal);
	void UpDownToNormal(const float &t);
	int  getUpperSide() const
	{
		return this->y() - (float(_height) / 4) - 20;
	}
	int  getLowerSide() const
	{
		return this->y() + (float(_height) / 3);
	}

public:

#pragma region Get-Set Properties
	RECT  View()const
	{
		return _viewRect;
	}

	long curMapWidth() const
	{
		return _curMapWidth;
	}

	long curMapHeight() const
	{
		return _curMapHeight;
	}

	void setCurMapWidth(const long &curMapWidth)
	{
		_curMapWidth = curMapWidth;
	}

	void setCurMapHeight(const long &curMapHeight)
	{
		_curMapHeight = curMapHeight;
	}

	void setPositionCharacter(const float& x, const float& y)
	{
		_positionCharacter.x = x;
		_positionCharacter.y = y;
	}

	void setSpecialState(const int &newState )
	{
		_specialState = newState;
		
	}
	void setIsAbsorbed(const bool isAbsorbed)
	{
		_isAbsorbed = isAbsorbed;
	}

	void setBoundingCharacter(const RECT &newRect)
	{
		_boundingCharacter = newRect;
	}

	bool IsCharacterDying() const
	{
		return _isCharacterDying;
	}

	void setCharacterDying(const bool  & value)
	{
		_isCharacterDying = value;
	}

#pragma endregion 

};
#endif
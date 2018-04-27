#include "dxgraphics.h"
#include "game.h"
#include <map>
#include "Camera.h"
#include "trace.h"
#include "Scene1.h"

#define MAX_LOOKUP -CHARACTER_VX*5
#define MAX_LOOKDOWN CHARACTER_VX*5 
#define BORDER_SIZE 25*SCALE_RATE;


MyCamera* MyCamera::_instance = NULL;
MyCamera * MyCamera::GetInstance()
{
	if (!_instance)
		_instance = new MyCamera();

	return _instance;
}

MyCamera::~MyCamera()
{
}

MyCamera::MyCamera()
{
	_width = SCREEN_WIDTH / SCALE_RATE;		//width of viewRect
	_height = SCREEN_HEIGHT / SCALE_RATE;	//height of viewRect
	_viewRect = RECT();
	_position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	_anchor = MIDDLE;
	CalAnchorPoint();

	_curFace = Face::RIGHT;
	_maxLookRight = _vxTranslate = _vyTranslate = _distanceLeftRight = _distanceUpDown = _specialState = 0;
	_isUpdateLeftRight = true;

	while (_maxLookRight < float(_width) / 6 + CHARACTER_VX * FIXED_TIME)
	{
		_maxLookRight += CHARACTER_VX * FIXED_TIME;
	}
	_maxLookLeft = -_maxLookRight;
}

void MyCamera::Update(float t)
{
#pragma region Update Camera Left-Right Position
	if (_isCharacterDying)
	{
		goto UpdateUpDown;
	}

	//Decide UpDateLeftRightOrNOt
	if (_specialState == 0) // if it is special state : fix camera 's position as  character's
	{
		//if Camera position make bounding reach end side of the map 
		if (_positionCharacter.x <= width() / 2
			|| _positionCharacter.x >= curMapWidth() - width() / 2
			)
		{
			if (_positionCharacter.x == width() / 2
				|| _positionCharacter.x == curMapWidth() - width() / 2
				)
			{
				if (!_isAbsorbed)
					UpdateLeftRight(t);
				_distanceLeftRight += _vxTranslate*t;
				_position.x += _vxTranslate;
			}
			else
			{
				_vx = 0;
				_distanceLeftRight = 0;
				_vxTranslate = 0;
			}
		}
		else
		{
			if (!_isAbsorbed) 
				UpdateLeftRight(t);
			_distanceLeftRight += _vxTranslate*t;
			_position.x += _vxTranslate;
		}

		//set position x by position of character
		if (_distanceLeftRight == 0)
		{
			_position.x = _positionCharacter.x - _vx*t;
		}
		_position.x += _vx*t;
	}
	else
	{
		_distanceLeftRight = 0;
		_position.x = _positionCharacter.x;
	}

	//A Raw Way Lock camera X bounding inside map
	if (_position.x < _width / 2)
		_position.x = _width / 2;
	if (_position.x > _curMapWidth - _width / 2)
	{
		_position.x = _curMapWidth - _width / 2;
	}
#pragma endregion 

	UpdateUpDown:

#pragma region Update Camera Up-Down Position
				//If character exceedes upper side of camera
				if (_boundingCharacter.top <= getUpperSide())
				{
					_vy > 0 ? _vy = 0 : _vy = _vy;
				}
				else
				{
					//If character exceedes lower side of camera
					if (_boundingCharacter.bottom >= getLowerSide())
					{
						_vy < 0 ? _vy = 0 : _vy = _vy;
					}
					else
						_vy = 0;
				}
				if (_position.y + _vxTranslate < _height / 2)
					_vyTranslate = 0;
				if (_position.y + _vyTranslate > _curMapHeight / 2 - _height / 2)
					_vyTranslate = 0;


				_distanceUpDown += _vyTranslate*t;
				_position.y += _vy*t + _vyTranslate*t;

				//A raw way to lock camera Y bounding inside map
				if (_position.y < _height / 2)
					_position.y = _height / 2;
				if (_position.y > _curMapHeight / 2 - _height / 2)
					_position.y = _curMapHeight / 2 - _height / 2;

#pragma endregion  


#pragma region Update Camera ViewRect and BoundingBox
				//Caculate view rect accordding to position and width height
				_viewRect.left = _position.x - _width / 2;
				_viewRect.right = _position.x + _width / 2;
				_viewRect.top = -_height / 2 + _position.y;
				_viewRect.bottom = _viewRect.top + _height;

				//Caculate Extraview (which is also a larger bounding box of camera - use for scan quadtree)
				_boundingBox = ExtraView();
#pragma endregion 
}


#pragma region ExtraView And BoundingBox

RECT MyCamera::ExtraView()
{
	RECT extraView;

	extraView.left = _viewRect.left - BORDER_SIZE;
	extraView.top = _viewRect.top - BORDER_SIZE;
	extraView.bottom = _viewRect.bottom + BORDER_SIZE;
	extraView.right = _viewRect.right + BORDER_SIZE;
	return extraView;
}

void MyCamera::RenderBounding(D3DCOLOR color, bool isRotation, bool isScale, bool isTranslation)
{
	setTranslation(D3DXVECTOR2(ExtraView().left - _viewRect.left, ExtraView().bottom - _viewRect.bottom));
	Transform(isRotation, isScale, isTranslation);

	RECT srect;
	srect.top = 0;
	srect.left = 0;
	srect.bottom = _height / 2;
	srect.right = _width / 2;

	sprite_handler->Draw(
		_boundingRect->image(),
		&srect,
		&CalAnchorPoint(TOP_LEFT),
		NULL,
		color
	);
	sprite_handler->SetTransform(&old_matrix);
}

#pragma endregion


#pragma region UPDOWN

void MyCamera::LookUp(const float &t, const bool & toNormal)
{
	_vyTranslate = -CHARACTER_VX;

	if (((_distanceUpDown + _vyTranslate*t <= MAX_LOOKUP || _distanceUpDown + _vyTranslate*t >= MAX_LOOKDOWN) && toNormal == false)
		|| _distanceUpDown + _vyTranslate*t <= (_height / 2 - _position.y)
		|| (toNormal == true && int(_distanceUpDown) == 0))
	{
		_vyTranslate = 0;
	}
}

void MyCamera::LookDown(const float &t, const bool & toNormal)
{
	_vyTranslate = CHARACTER_VX;
	if (((_distanceUpDown + _vyTranslate*t <= MAX_LOOKUP || _distanceUpDown + _vyTranslate*t >= MAX_LOOKDOWN) && toNormal == false)
		|| _distanceUpDown + _vyTranslate*t >= _curMapHeight / 2 - _height / 2 - _position.y
		|| (toNormal == true && int(_distanceUpDown) == 0))
	{
		_vyTranslate = 0;
	}
}

void MyCamera::UpDownToNormal(const float &t)
{
	_vyTranslate = 0;
	if (_distanceUpDown > 0)
	{
		LookUp(t, true);
	}
	if (_distanceUpDown < 0)
	{
		LookDown(t, true);
	}
}

#pragma endregion  


#pragma region LEFTRIGHT  

void MyCamera::LookLeft(const float &t, const bool & toNormal)
{
	_vxTranslate = -CHARACTER_VX *0.7;

	if (((_distanceLeftRight + _vxTranslate*t <= _maxLookLeft || _distanceLeftRight + _vxTranslate*t >= _maxLookRight) && toNormal == false)
		|| (toNormal == true && int(_distanceLeftRight) == 0))
	{
		_vxTranslate = 0;
	}

}

void MyCamera::LookRight(const float &t, const bool & toNormal)
{
	_vxTranslate = CHARACTER_VX *0.7;

	if (((_distanceLeftRight + _vxTranslate*t <= _maxLookLeft || _distanceLeftRight + _vxTranslate*t >= _maxLookRight) && toNormal == false)
		|| (toNormal == true && int(_distanceLeftRight) == 0))
	{
		_vxTranslate = 0;
	}
}

void MyCamera::LeftRightToNormal(const float &t)
{
	if (_distanceLeftRight == 0)
	{
		_vxTranslate = 0;
	}
	if (_distanceLeftRight > 0)
	{
		LookLeft(t, true);
	}
	if (_distanceLeftRight < 0)
	{
		LookRight(t, true);
	}
}

void MyCamera::UpdateLeftRight(const float &t)
{
	if (_vx == 0)
	{
		if (this->curface() == Face::LEFT)
			LookLeft(t, false);
		else
			LookRight(t, false);
	}
	else
	{
		LeftRightToNormal(t);
	}
}
#pragma endregion 
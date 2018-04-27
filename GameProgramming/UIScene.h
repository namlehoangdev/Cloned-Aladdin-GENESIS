#pragma once
#ifndef _UI_SCENE1_
#define _UI_SCENE1_
#include "sprite.h"
#include <vector>
#include "GameObject.h"

class UIScene
{
private:
	Sprite* _healthIcon;
	Sprite* _UPIcon;
	Sprite* _appleIcon;
	Sprite* _diamondIcon;
	Sprite* _numberSprite;
	RECT _healthRect;
	int _healthState;

public:
	int healthState() const
	{
		return _healthState;
	}

	void setHealthState(int healthState)
	{
		_healthState = healthState;
	}

private:
	//RECT _UPRect; 
	//RECT _appleRect; 
	//RECT _diamondRect; 
	//RECT _scoreRect; 
	//ID3DXFont* _font;
	//ID3DXFont* _fontBorder;
	//ID3DXFont* _fontShadow; 
	std::vector<RECT> *_vectNumberCount;
	std::vector<RECT> *_vectNumberScore;
	GameObject* _healthLamp;

public:
	GameObject* healthLamp() const
	{
		return _healthLamp;
	}

	void setHealthLamp(GameObject* healthLamp)
	{
		_healthLamp = healthLamp;
	}

private:
	int _animScoreDelay;
	int _animCount;
	int _displayScore;
	void CalculateHealthBar(int health);
public:
	UIScene();
	~UIScene();
	void Render(int health, int UP, int appleCount, int diamondcount, int point);
	//void RenderText(int UP, int appleCount, int diamondCount=0, int score=0);
	void LoadFontXML(char * filePath);
	void RenderNumber(D3DXVECTOR3 startposition, int number, bool isAlignLeft = false, bool isNumberScore = false);
};

#endif

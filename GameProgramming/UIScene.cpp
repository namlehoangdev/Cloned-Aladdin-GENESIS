#include "UIScene.h"
#include "dxgraphics.h"
#include "game.h"
#include "Math.h"
#include "String"
#define MAX_HEALTH 10


RECT healtletterRect;



UIScene::UIScene()
{
	_healthIcon = new Sprite("Res/healthIcon.png", 150, 50);
	_UPIcon = new Sprite("Res/UPicon.png", 50, 50);
	_appleIcon = new Sprite("Res/appleIcon.png", 100, 100);
	_diamondIcon = new Sprite("Res/DiamondIcon.png", 5, 5);
	_numberSprite = new Sprite("Res/Number.png", 300, 300);
	_vectNumberCount = new std::vector<RECT>;
	_vectNumberScore = new std::vector<RECT>;
	LoadFontXML("Res/NumberXML.xml");
	_displayScore = 0;
	_animCount = 0;
	_animScoreDelay = 3;


	_healthLamp = new GameObject();
	_healthLamp->setPosition(20, 20 * SCALE_RATE);
	_healthLamp->setSprite(new Sprite("Res\\LampVip.png", 246, 66));
	_healthLamp->set_state_manager(new StateManager("Res\\HealthLampEnhancedXML.xml"));

	_healthLamp->state_manager()->AddToDictState("9", "9");
	_healthLamp->state_manager()->AddToDictState("8", "8");
	_healthLamp->state_manager()->AddToDictState("7", "7");
	_healthLamp->state_manager()->AddToDictState("6", "6");
	_healthLamp->state_manager()->AddToDictState("5", "5");
	_healthLamp->state_manager()->AddToDictState("4", "4");
	_healthLamp->state_manager()->AddToDictState("3", "3");
	_healthLamp->state_manager()->AddToDictState("2", "2");
	_healthLamp->state_manager()->AddToDictState("1", "1");
	_healthLamp->state_manager()->setState("9");
	_healthLamp->setAnchor(AnchorPoint::BOTTOM_LEFT);


}
void UIScene::Render(int health, int UP, int appleCount, int diamondCount, int score)
{
	sprite_handler->SetTransform(&old_matrix); 
	_healthLamp->GraphicUpdate(FIXED_TIME);
	_healthLamp->setScale(D3DXVECTOR2(2, 2));
	if ((_healthLamp->index() % 2 == 0 && health < 4) || health >= 4)
	{
		_healthLamp->Render(false, true, true);
	}


	D3DXVECTOR3 position;
	if (UP > 0)
	{
		sprite_handler->Draw(_UPIcon->image(), NULL, NULL, new D3DXVECTOR3(20, SCREEN_HEIGHT*0.85 / SCALE_RATE, 0), D3DCOLOR_XRGB(255, 255, 255));
		position = D3DXVECTOR3(20 + SCALE_RATE * 33, SCREEN_HEIGHT*0.85 + SCALE_RATE * 13, 0);
		RenderNumber(position, UP);
	}

	if (appleCount > 0)
	{
		if ((_healthLamp->index() % 2 == 0 && appleCount < 6) || appleCount >= 6)
		{
			sprite_handler->Draw(_appleIcon->image(), NULL, NULL, new D3DXVECTOR3(SCREEN_WIDTH*0.84 / SCALE_RATE, SCREEN_HEIGHT*0.85 / SCALE_RATE, 0), D3DCOLOR_XRGB(255, 255, 255));
		}
		position = D3DXVECTOR3(SCREEN_WIDTH*0.7 + SCALE_RATE * 23, SCREEN_HEIGHT*0.85 + SCALE_RATE * 13, 0);
		RenderNumber(position, diamondCount);
	}

	if (diamondCount > 0)
	{
		sprite_handler->Draw(_diamondIcon->image(), NULL, NULL, new D3DXVECTOR3(SCREEN_WIDTH*0.7 / SCALE_RATE, SCREEN_HEIGHT*0.85 / SCALE_RATE, 0), D3DCOLOR_XRGB(255, 255, 255));
		position = D3DXVECTOR3(SCREEN_WIDTH*0.84 + SCALE_RATE * 23, SCREEN_HEIGHT*0.85 + SCALE_RATE * 13, 0);
		RenderNumber(position, appleCount);
	}

	if (score == 0)
		return;

	_animCount++;
	if (_animCount >= _animScoreDelay)
	{
		if (_displayScore < score)
		{
			_displayScore += 50;
		}
		_animCount = 0;
	}
	position = D3DXVECTOR3(SCREEN_WIDTH*0.84 + SCALE_RATE * 23, 20 * SCALE_RATE, 0);
	RenderNumber(position, _displayScore, true, true);
	 
}



void UIScene::RenderNumber(D3DXVECTOR3 startposition, int number, bool isAlignLeft, bool isNumberScore)
{
	string strNumber = to_string(number);
	D3DXVECTOR3 position = startposition;
	D3DXMATRIX matScale;
	D3DXMATRIX matTranslate;
	D3DXMatrixTranslation(&matScale, 1, 1, 0);
	D3DXMatrixTranslation(&matTranslate, 1, 1, 0);


	sprite_handler->SetTransform(&(matScale * matTranslate));
	if (isAlignLeft == false)
	{
		for (int i = 0; i < strNumber.length(); i++)
		{
			int index = (strNumber[i] - 48);

			sprite_handler->Draw(
				_numberSprite->image(),
				isNumberScore == false ? &_vectNumberCount->at(index) : &_vectNumberScore->at(index),
				NULL,
				&position,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 nextPosition;
			position.y = position.y;

			position.x = position.x + _vectNumberCount->at(index).right - _vectNumberCount->at(index).left;
		}
	}
	else
	{

		for (int i = strNumber.length() - 1; i >= 0; i--)
		{
			int index = (strNumber[i] - 48);

			sprite_handler->Draw(
				_numberSprite->image(),
				isNumberScore == false ? &_vectNumberCount->at(index) : &_vectNumberScore->at(index),
				NULL,
				&position,
				D3DCOLOR_XRGB(255, 255, 255));

			D3DXVECTOR3 nextPosition;
			position.y = position.y;
			position.x = position.x - (_vectNumberScore->at(index).right - _vectNumberScore->at(index).left);

		}
	}
	sprite_handler->SetTransform(&old_matrix);

	sprite_handler->SetTransform(&old_matrix);



}
void UIScene::LoadFontXML(char* filePath)
{
	xml_document fileXml;
	xml_parse_result result = fileXml.load_file(filePath);
	xml_node root = fileXml.child("Animations");

	for (xml_node nodeAnimation = root.first_child(); nodeAnimation; nodeAnimation = nodeAnimation.next_sibling())
	{
		string name = nodeAnimation.attribute("name").value();

		if (name == "NumberCount") {
			for (xml_node nodeRec = nodeAnimation.first_child(); nodeRec; nodeRec = nodeRec.next_sibling())
			{
				RECT rect;
				rect.top = atoi(nodeRec.attribute("y").value());
				rect.left = atoi(nodeRec.attribute("x").value());
				rect.bottom = atoi(nodeRec.attribute("h").value()) + rect.top;
				rect.right = atoi(nodeRec.attribute("w").value()) + rect.left;
				_vectNumberCount->push_back(rect);
			}
			continue;
		}

		if (name == "NumberScore") {
			for (xml_node nodeRec = nodeAnimation.first_child(); nodeRec; nodeRec = nodeRec.next_sibling())
			{
				RECT rect;
				rect.top = atoi(nodeRec.attribute("y").value());
				rect.left = atoi(nodeRec.attribute("x").value());
				rect.bottom = atoi(nodeRec.attribute("h").value()) + rect.top;
				rect.right = atoi(nodeRec.attribute("w").value()) + rect.left;
				_vectNumberScore->push_back(rect);
			}
			continue;
		}
	}
}


UIScene::~UIScene()
{
}

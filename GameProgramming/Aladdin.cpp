#include "Aladdin.h"
#include "dxgraphics.h"
#include <dinput.h>
#include "game.h"
#include "Camera.h"
#include "trace.h"
#include "GameManager.h"
#include "dxinput.h"
#define BULLET_VX 15
#define BULLET_VY 4
#define JUMP_ACCELERATE 2


//for situational purpose
AppleBullet* temp_bullet_object;
AppleBullet* temp_bullet_object2;




Aladdin::Aladdin()
{
	//OutputDebugString("Tao ra alddin");
	//temp instance to increase performance
	temp_bullet_object = new AppleBullet();
	temp_bullet_object2 = new AppleBullet();
	_soundRespawn = LoadSound("Res/Audio/ContinuePoint.wav");
	_jumpStepRemaining = 0;
	_isAbsorbed = false;
	_minX = 0;
	_maxX = GameManager::GetInstance()->GetCurrentScene()->MapInfo()->Width;
	_isThrowing = false;
	_distanceFromMain = 9999;
	_index = 0;
	_animaDelay = 1.0f;
	_animaCount = 0;
	_health = 9;
	_invicibleTime = 10;
	_curFace = Face::RIGHT;
	_lastFace = _curFace;
	_mainState = "0";
	_subState = "0";
	_handState = "0";
	_sword = new RECT();
	_stateManager = new StateManager("Res\\AladdinXML.xml");
	this->setSprite(new Sprite("Res\\Aladdin.png", 40, 50));
	_stateManager->AddToDictState("000", "Idle1");
	//these state is temporary and illogic
	_stateManager->AddToDictState("0001", "RunSkid");
	_stateManager->AddToDictState("0002", "FallHeavy");
	_stateManager->AddToDictState("0003", "FallLight");
	_stateManager->AddToDictState("005", "StartIdle2");
	_stateManager->AddToDictState("006", "Idle2");
	_stateManager->AddToDictState("007", "Idle3");
	_stateManager->AddToDictState("410", "Climb");
	_stateManager->AddToDictState("010", "IdleFall");
	_stateManager->AddToDictState("020", "IdleJump");
	_stateManager->AddToDictState("001", "IdleThrow");
	_stateManager->AddToDictState("002", "IdleSlash");
	_stateManager->AddToDictState("052", "SwingSlash");
	_stateManager->AddToDictState("051", "SwingThrow");
	_stateManager->AddToDictState("050", "SwingIdle");
	_stateManager->AddToDictState("100", "Run");
	_stateManager->AddToDictState("110", "RunFall");
	_stateManager->AddToDictState("120", "RunJump");
	_stateManager->AddToDictState("101", "RunThrow");
	_stateManager->AddToDictState("300", "IdleDown");
	_stateManager->AddToDictState("200", "IdleUp");
	_stateManager->AddToDictState("102", "RunSlash");
	_stateManager->AddToDictState("202", "IdleUpSlash");
	_stateManager->AddToDictState("302", "IdleDownSlash");
	_stateManager->AddToDictState("022", "RunSlash");
	_stateManager->AddToDictState("012", "RunSlash");
	_stateManager->AddToDictState("122", "RunSlash");
	_stateManager->AddToDictState("112", "RunSlash");
	_stateManager->AddToDictState("301", "IdleDownThrow");
	_stateManager->AddToDictState("130", "Push");
	_stateManager->AddToDictState("400", "Climb");
	_stateManager->AddToDictState("420", "ClimbJump");
	_stateManager->AddToDictState("250", "SwingIdle");
	_stateManager->AddToDictState("450", "SwingIdle");
	_stateManager->AddToDictState("550", "SwingIdle");
	_stateManager->AddToDictState("150", "Swing");
	_stateManager->AddToDictState("402", "ClimbSlash");
	_stateManager->AddToDictState("401", "SwingThrow");
	_stateManager->AddToDictState("060", "Spin");
	_stateManager->AddToDictState("160", "Spin");
	_stateManager->AddToDictState("0004", "Beaten");
	_stateManager->AddToDictState("600", "Death1");
	_stateManager->AddToDictState("0005", "Respawn");
	_stateManager->AddToDictState("700", "Win1");
	_stateManager->AddToDictState("800", "Win2");
	_stateManager->AddToDictState("900", "Win3");

	_bulletList = new list<AppleBullet*>();

	_appleCount = 10;
	_soundAladdinBeBeaten = LoadSound("Res/Audio/AladdinHitted.wave");
	_soundAppleEmty = LoadSound("Res/Audio/AppleThrowEmty.wave");
	_soundThrowApple = LoadSound("Res/Audio/AppleThrow.wave");
}


Aladdin::~Aladdin()
{
	//OutputDebugString("Giai phong alddin");
	_bulletList->clear();
	delete(_bulletList);
}

RECT Aladdin::NextBounding()
{
	return RECT();
}

void Aladdin::FireApple()
{

	if (_appleCount > 0)
	{
		D3DXVECTOR3 newPos;
		if (curface() == Face::RIGHT)
			newPos = this->CalPositon(TOP_RIGHT);
		else
		{
			newPos = this->CalPositon(TOP_LEFT);
		}
		temp_bullet_object->set_is_popping(false);
		temp_bullet_object->setVisible(true);
		temp_bullet_object->state_manager()->setState("000");
		temp_bullet_object->Reset();//reset animation
		temp_bullet_object->setPosition(newPos.x, newPos.y);

		//trai tao thu 2
		temp_bullet_object2->set_is_popping(false);
		temp_bullet_object2->setVisible(true);
		temp_bullet_object2->state_manager()->setState("000");
		temp_bullet_object2->Reset();//reset animation
		if (curface() == Face::RIGHT)
		{
			temp_bullet_object2->setPosition(newPos.x + 5, newPos.y);
		}
		else
		{
			temp_bullet_object2->setPosition(newPos.x - 5, newPos.y); 
		}

		if (_curFace == Face::RIGHT)
		{
			temp_bullet_object->set_vx(BULLET_VX);
			//trai tao thu 2
			temp_bullet_object2->set_vx(BULLET_VX);
		}
		else
		{
			temp_bullet_object->set_vx(-BULLET_VX);
			//trai tao thu 2
			temp_bullet_object2->set_vx(-BULLET_VX);

		}
		if (isSwinging() == true)
		{
			temp_bullet_object->set_vy(BULLET_VY * 2);
			temp_bullet_object2->set_vy(BULLET_VY * 2);
		}
		else
		{
			temp_bullet_object->set_vy(BULLET_VY);
			temp_bullet_object2->set_vy(BULLET_VY); 
		}
		_bulletList->push_back(temp_bullet_object);
		_bulletList->push_back(temp_bullet_object2);
		_soundThrowApple->Play();
		_appleCount -= 2;
		_isThrowing = true;
	}
	else
	{
		_soundAppleEmty->Play();
	}

}

void Aladdin::Init()
{
}

void Aladdin::PhysicUpdate(float t)
{
	GameObjectMove::PhysicUpdate(t);
	if (degree_state() == "5")
		_isImmune = 10.0f;
	if (jump_step_remaining() != 0)
	{
		_vy += JUMP_ACCELERATE;
		_jumpStepRemaining--;
	}
	if (this->hand_state() != "0" && this->state_manager()->life_span() < 0)
		this->set_hand_state("0");
	if (isClimbing() == false && main_state() == "4")
		_mainState = "0";
	if (this->vx() != 0 && _isAbsorbed == false)
	{
		if (this->vx() > 0)
		{
			this->set_curFace(GameObject::Face::RIGHT);
			MyCamera::GetInstance()->set_curFace(GameObject::Face::RIGHT);
		}
		else
		{
			this->set_curFace(GameObject::Face::LEFT);
			MyCamera::GetInstance()->set_curFace(GameObject::Face::LEFT);
		}
		if (this->CheckFlip())
		{
			_vx = -_vx;
			this->Flip();
		}
	}

	if (_position.x < 0)
	{
		_position.x = _width;
	}
	if (_position.x > MyCamera::GetInstance()->curMapWidth())
	{
		_position.x = MyCamera::GetInstance()->curMapWidth() - _width;
	}
	if (_position.y < 0)
	{
		_position.y = _height;
	}
	if (_position.y > MyCamera::GetInstance()->curMapHeight() / 2)
	{
		_position.y = MyCamera::GetInstance()->curMapHeight() / 2 - _height;
	}



	//for (auto it = _bulletList->begin(); it != _bulletList->end(); )
	//{/*
	//	if ((temp_bullet_object->is_popping() == true && temp_bullet_object->state_manager()->life_span() == 0) || (SimpleIntersect(&MyCamera::GetInstance()->ExtraView(), &temp_bullet_object->bounding_box()) == false))
	//	{
	//		it = _bulletList->erase(it);
	//		temp_bullet_object->setVisible(false);
	//		_isThrowing = false;
	//	}
	//	else*/
		//{ 
			//temp_bullet_object = *it;
			temp_bullet_object->set_vy(temp_bullet_object->vy()*1.1f);
			temp_bullet_object->setPosition(temp_bullet_object->x() + temp_bullet_object->vx()*t, temp_bullet_object->y() + temp_bullet_object->vy()*t);
			//it++;
		//}

			temp_bullet_object2->set_vy(temp_bullet_object2->vy()*1.1f);
			temp_bullet_object2->setPosition(temp_bullet_object2->x() + temp_bullet_object2->vx()*t, temp_bullet_object2->y() + temp_bullet_object2->vy()*t);
	

}



void Aladdin::GraphicUpdate(float t)
{
	_animaCount++;
	_animaDelay = _stateManager->curState().AnimaDelay();

	if (_animaCount >= _animaDelay)
	{
		string name = _stateManager->curState().getName();

		if (name == "Win1" || name == "Win2")
		{
			Next();
			goto Another;
		}
		if (main_state() == "0"
			|| name == "ClimbJump"
			|| name == "IdleUp"
			|| name == "IdleDown"
			|| (sub_state() == "1" && name != "Climb")
			|| sub_state() == "2"
			|| hand_state() != "0"
			|| degree_state() != "0"
			|| name == "Death1"
			|| name == "Respawn"

			)
		{
			Next2();
			if (_index == _stateManager->curState().getListRect().size() - 1)
			{
				if (name == "IdleUp")
				{
					MyCamera::GetInstance()->LookUp(t, false);
					//	OutputDebugString("\nUpUpUp"); 
					goto Finish;
				}
				if (name == "IdleDown")
				{
					MyCamera::GetInstance()->LookDown(t, false);
					//	OutputDebugString("\nDownDownDown"); 
					goto Finish;
				}

				if (name == "Idle1" || name == "Idle2" || name == "Idle3" || name == "StartIdle2")
				{
					if (name == "Idle1")
					{
						_randomIdleCount++;
						if (_randomIdleCount == 3)
						{
							_stateManager->setLastState("000");
							setState("005");
							_randomIdleCount = 0;
						}
						Reset();
						goto Another;
					}

					if (name == "StartIdle2")
					{
						_stateManager->setLastState("005");
						_randomIdle = 6 + (rand() % static_cast<int>(2));
						setState("00" + to_string(_randomIdle));
						Reset();
						goto Another;
					}

					if (_stateManager->lastState().getName() == "StartIdle2")
					{
						_randomIdle = 6 + (rand() % static_cast<int>(2));
						setState("00" + to_string(_randomIdle));
						Reset();
						goto Another;
					}

					if (name == "Idle2")
					{
						_randomIdleCount++;
						if (_randomIdleCount == 3)
						{
							_stateManager->setLastState("005");
							_randomIdleCount = 0;
							Reset();

						}
						goto Another;

					}

					if (name == "Idle3")
					{
						_randomIdleCount++;
						if (_randomIdleCount == 1)
						{
							_stateManager->setLastState("005");
							_randomIdleCount = 0;
							Reset();
						}
						goto Another;

					}
				}
			}
		}
		else
		{

			if ((name == "Climb" && _vy < 0) || name != "Climb")
			{
				Next();
			}
			if (name == "Climb" && _vy > 0)
			{
				Back();
			}
		}
		//		OutputDebugString("\nUpDownToNormal"); 
	Another:
		/*_width = _stateManager->curState().getListRect().at(_index).right - _stateManager->curState().getListRect().at(_index).left;
		_height = _stateManager->curState().getListRect().at(_index).bottom - _stateManager->curState().getListRect().at(_index).top;*/
		_animaCount = 0;

		// update lai anchorpoint do frame co bounding khac nhau
		//CalAnchorPoint();
		//	this->state_manager()->set_life_span(this->state_manager()->life_span() - 1);
		if (this->state_manager()->life_span() == 0 && (this->hand_state() == "1" || this->hand_state() == "2"))
		{
			this->set_hand_state("0");
		}
	}

	MyCamera::GetInstance()->UpDownToNormal(t);

Finish:

	CalAnchorPoint();

	(this->isSwinging() == true || this->isClimbing() == true || _health == 0) ?
		MyCamera::GetInstance()->setSpecialState(1) : MyCamera::GetInstance()->setSpecialState(0);

	MyCamera::GetInstance()->setIsAbsorbed(_isAbsorbed);

	if (_isDying == true)
	{
		_isClimbing = false;
		_isSetStatePush = false;
		_isSwinging = false;
		_isAbsorbed = false;
		_isWalkingStairs = false;
		_isImmune = true;
		_onStateEnd = false;

	}

	if (_isDying == true && _index == _stateManager->curState().getListRect().size() - 1 && _stateManager->curState().getName() == "Death1")
	{
		this->setPosition(MyCamera::GetInstance()->x(), this->y());
	}


	if (_isDying == true && _index == _stateManager->curState().getListRect().size() - 1
		&& _stateManager->curState().getName() != "Win1" && _stateManager->curState().getName() != "Win2" && _stateManager->curState().getName() != "Win3")
	{

		if (_life > 0)
		{
			_isDying = false;
			_life -= 1;
			set_health(9);
			this->setPosition(_positionCheckpoint.x, _positionCheckpoint.y - 8);


			if (_positionCheckpoint.x > 2000)
			{
				MyCamera::GetInstance()->setPosition(this->Position());
				this->setState("0005");
				if (_soundRespawn->IsSoundPlaying() == false)
					PlaySound(_soundRespawn);
				this->set_degree_state("5");
				Reset();

			}
			else
			{
				_chosenLayer = 0;
			}
		}
	}

	MyCamera::GetInstance()->setPositionCharacter(this->x(), this->y());
	MyCamera::GetInstance()->setBoundingCharacter(CalculateBoundingBox(this->x(), this->y(), _width, _height, _anchor));
	MyCamera::GetInstance()->set_vx(_vx);
	MyCamera::GetInstance()->set_vy(_vy);
	MyCamera::GetInstance()->setCharacterDying(_isDying);
}




void Aladdin::Back()
{

	int size = _stateManager->curState().getListRect().size() - 1;
	if (_index > 0)
		_index = (_index - 1) % size;
	else
		_index = size;

}




void Aladdin::DrawBullet()
{
	/*for (list<AppleBullet*>::iterator i = _bulletList->begin(); i != _bulletList->end(); i++)
	{
		temp_bullet_object = *i;
		if (temp_bullet_object->Visbile() == true)
		{
			temp_bullet_object->setTranslation(D3DXVECTOR2(temp_bullet_object->x() - MyCamera::GetInstance()->View().left, temp_bullet_object->y() - MyCamera::MyCamera::GetInstance()->View().top));
			temp_bullet_object->UpdateAnimate();
			temp_bullet_object->Render();
		}

	}*/

	temp_bullet_object->setVisible(true);
	temp_bullet_object->setTranslation(D3DXVECTOR2(temp_bullet_object->x() - MyCamera::GetInstance()->View().left, temp_bullet_object->y() - MyCamera::MyCamera::GetInstance()->View().top));
	temp_bullet_object->UpdateAnimate();
	temp_bullet_object->Render();
	temp_bullet_object2->setVisible(true);
	temp_bullet_object2->setTranslation(D3DXVECTOR2(temp_bullet_object2->x() - MyCamera::GetInstance()->View().left, temp_bullet_object2->y() - MyCamera::MyCamera::GetInstance()->View().top));
	temp_bullet_object2->UpdateAnimate();
	temp_bullet_object2->Render();


}

void Aladdin::setState(string newState)
{
	if (_stateManager->dict_state()[newState] == "")
		return;
	if (_isWalkingStairs == true && _vx != 0)
	{
		newState = "10" + hand_state();
		_isWalkingStairs = false;
	}
	if (_stateManager->curState().getName() != _stateManager->dict_state()[newState]
		&& isAllowChangeState(newState) == true)
	{
		Reset();
		_stateManager->setLastState(_stateManager->curState().getName());
		_stateManager->setState(newState);

	}

}





void Aladdin::Reset()
{
	_index = 0;
}

void Aladdin::BeBeaten()
{

	if (_isImmune == 0 && health() != 0)
	{

		//set_health(_health - 1);
		_isImmune = 40;
		_soundAladdinBeBeaten->Play();
		if (_health <= 0)
		{
			_isDying = true;
			setState("600");
			_degreeState = "6";
			return;
		}


		if (isSwinging() == false && isClimbing() == false)
		{
			set_state("0004");
			_degreeState = "4";
			_onStateEnd = true;
		}

	}




}

string Aladdin::CurrentState()
{
	return _stateManager->curState().getName();
}


AppleBullet::AppleBullet()
{
	_isRepeating = false;
	this->setAnchor(TOP_LEFT);
	this->setSprite(new Sprite("Res\\Aladdin.png", 7, 6));
	this->set_state_manager(new StateManager("Res\\AppleBullet.xml"));
	this->state_manager()->AddToDictState("000", "flying");
	this->state_manager()->AddToDictState("001", "popping");
	this->state_manager()->setState("000");
}

AppleBullet::AppleBullet(int x, int y, Face face)
{

	_isPopping = false;
	if (face == Face::RIGHT)
		_vx = BULLET_VX;
	else
		_vx = -BULLET_VX;

	_vy = BULLET_VY;
	_isRepeating = false;
	this->setAnchor(TOP_LEFT);
	this->setPosition(x, y);
	this->setSprite(new Sprite("Res\\Aladdin.png", 7, 6));
	this->set_state_manager(new StateManager("Res\\AppleBullet.xml"));
	this->state_manager()->AddToDictState("000", "flying");
	this->state_manager()->AddToDictState("001", "popping");
	this->state_manager()->setState("000");

}
void Aladdin::Render(bool isRotation, bool isScale, bool isTranslation)
{
	Transform(isRotation, isScale, isTranslation);
	if (_index >= _stateManager->curState().getListRect().size())
		return;
	_width = _stateManager->curState().getListRect().at(_index).right - _stateManager->curState().getListRect().at(_index).left;
	_height = _stateManager->curState().getListRect().at(_index).bottom - _stateManager->curState().getListRect().at(_index).top;
	CalAnchorPoint();

	if ((_stateManager->curState().getName() == "Beaten" && _index % 2 == 0) || _stateManager->curState().getName() != "Beaten")
	{
		sprite_handler->Draw(
			_sprite->image(),
			//_stateManager == NULL ? NULL : &_stateManager->curState().getListRect().at(_index),
			_stateManager->curState().getName() == "" ? NULL : &_stateManager->curState().getListRect().at(_index),
			//NULL,
			&_anchorPoint,
			NULL,
			D3DCOLOR_XRGB(255, 255, 255)
		);
	}

	sprite_handler->SetTransform(&old_matrix);

	_width = _stateManager->curState().MinBounding().right - _stateManager->curState().MinBounding().left;
	_height = _stateManager->curState().MinBounding().bottom - _stateManager->curState().MinBounding().top;
	_boundingBox = CalculateBoundingBox(x(), y(), _width, _height, _anchor);
	CalAnchorPoint();
}


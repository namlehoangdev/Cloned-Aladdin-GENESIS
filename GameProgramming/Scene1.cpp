#include "Scene1.h"
#include "dxinput.h"
#include "GameTime.h"
#include "trace.h"
#include "Quadtree.h"
#include "Camera.h"
#include "ApplePrefab.h"


#include "EnemyThinPrefab.h"
#include "EnemyMusPrefab.h"
#include "EnemyFatPrefab.h"
#include "EnemyJugPrefab.h"
#include "EnemyJarPrefab.h"

#include "RopePrefab.h"
#include "GroundPrefab.h"
#include "WallPrefab.h"
#include "HorizontalBarPrefab.h"


#include "CamelPrefab.h"


#include "FloatGroundPrefab.h"
#include "SpringBoardPrefab.h"
#include "BulletPrefab.h"
#include "ExplosionPrefab.h"
#include "TriggerPrefab.h"
#include "ShopperPrefab.h"
#include "StairsPrefab.h"
#include "FireGroundPrefab.h"
#include "EnemyHandPrefab.h"
#include "BurningEffectPrefab.h"
#include "PotPrefab.h"
#include "GenieFacePrefab.h"
#include "AbuFacePrefab.h"
#include "HeartPrefab.h"
#include "DiamondPrefab.h"
#include "CheckpointJarPrefab.h"
#include "GenieLampPrefab.h"
#include "ShopperTextPrefab.h"
#include "CeilingPrefab.h"
#include "SceneHome.h"
#include "GameManager.h"
#include "Scene2.h"


#define GRAVITY 1
//#define JUMP_FORCE -41
#define STOP_TRACKING_DISTANCE 40
#define BOUNDARY_STAIRS 583
#define JUMP_STAIRS -2
#define JUMP_STEP 9
#define JUMP_FORCE -21



//float countForFat;

HRESULT result;
//For allocating purpose
Pot* temp_pot_bullet;
list<Pot*>* pot_list;
bool assigned;

vector<D3DXVECTOR3> initFloatGroundList;
list<GameObject*>* listFireGround;
list<GameObject*>* listSpringBoard;
GameObject* tempFireGround;
GameObject* tempTrigger;
list<GameObject*>* floatGroundList;
CollisionResult* _bulletCollide;
GameObjectMove* temp_object_move;
GameObjectMove* temp_object_jug;

GameObject* temp_burnfx;
GameObjectMove* camel_target;
GameObject* temp_bullet_enemy;
GameObject* temp_object;
AppleBullet* temp_bullet;
GameObject* camel_saliva;
//timing variable
DWORD start = GetTickCount();
GameObject *TriggerLeft = new GameObject();
GameObject *TriggerRight = new GameObject();
GameObject *Shopper = new GameObject();
GameObject *ShopperText = new GameObject();

//initializes the game
Scene1::Scene1()
{

}
int Scene1::Game_Init(HWND hwnd)
{
	Game::Game_Init(hwnd);
	////initialize keyboard 
	//if (!Init_Keyboard(hwnd))
	//{
	//	MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
	//	return 0;
	//}
	//init object for operating
	assigned = false;
	tempTrigger = new GameObject();

	temp_bullet_enemy = new GameObject();
	pot_list = new list<Pot*>();
	temp_pot_bullet = new Pot();
	_camel = new GameObjectMove();
	camel_target = new GameObjectMove();
	listFireGround = new list<GameObject*>();
	listSpringBoard = new list<GameObject*>();
	tempFireGround = new GameObject();
	floatGroundList = new list<GameObject*>();
	temp_object_jug = new GameObjectMove();
	_bulletCollide = new CollisionResult();
	temp_burnfx = new GameObject();
	BurningEffectPrefab::Instantiate(temp_burnfx);
	camel_saliva = new GameObject();
	camel_saliva->set_name("CamelSaliva");
	BulletPrefab::Instantiate(camel_saliva, "CamelSaliva", 0, 0, _camel->curface());
	temp_object_move = new GameObjectMove();
	temp_object = new GameObject();
	temp_bullet = new AppleBullet();
	_gameObjectList = new list<GameObject*>();
	_onScreenList = new list<GameObject*>();
	_healthHavingList = new list<GameObjectMove*>();
	_disposableList = new list<GameObject*>();
	_itemsList = new list<GameObject*>();
	//load graphic source
	_explosion = new GameObject();

	LoadListObjectXml("Res/Scene1XML.xml");
	ExplosionPrefab::Instantiate(_explosion, 0, 0);
	_gameObjectList->push_back(_explosion);
	mapIdName["Apple"] = 0;
	mapIdName["Ground"] = 1;
	mapIdName["Wall"] = 2;
	mapIdName["Rope"] = 3;
	mapIdName["HorizontalBar"] = 4;
	mapIdName["FloatGround"] = 5;
	mapIdName["SpringBoard"] = 6;
	mapIdName["Camel"] = 7;
	mapIdName["Stairs"] = 8;
	mapIdName["Trigger"] = 31;
	mapIdName["EnemyThin"] = 11;
	mapIdName["EnemyMus"] = 12;
	mapIdName["EnemyFat"] = 13;
	mapIdName["EnemyJug"] = 14;
	mapIdName["EnemyJar"] = 15;
	mapIdName["EnemyHand"] = 20;
	mapIdName["Pot"] = 21;
	mapIdName["ParabolKnife"] = 16;
	mapIdName["StraightKnife"] = 17;
	mapIdName["CamelSaliva"] = 18;
	mapIdName["FireGround"] = 19;
	mapIdName["Shopper"] = 30;
	mapIdName["Diamond"] = 41;
	mapIdName["Heart"] = 42;
	mapIdName["AbuFace"] = 43;
	mapIdName["CheckpointJar"] = 44;
	mapIdName["GenieFace"] = 45;
	mapIdName["GenieLamp"] = 46;
	mapIdName["Ceiling"] = 47;


#pragma region Sound
	_soundWow = LoadSound("Res/Audio/Wow.wav");
	_soundTheme = LoadSound("Res/Audio/AgrabahMarket.wav");
	_soundSlash = LoadSound("Res/Audio/IdleDownSplash.wave");
	_soundPotFall = LoadSound("Res/Audio/ClayPot.wav");
	_soundCollectApple = LoadSound("Res/Audio/AppleCollect.wave");
	_soundCamel = LoadSound("Res/Audio/Camel.wave");
	_soundSpringBoard = LoadSound("Res/Audio/SpringBroad.wave");
	_soundAppleCollision = LoadSound("Res/Audio/AppleThrowCollision.wave");
	_soundFire = LoadSound("Res/Audio/FireFromCoal.wav");
	_soundHighSword = LoadSound("Res/Audio/HighSword.wav");
	_soundLowSword = LoadSound("Res/Audio/LowSword.wav");
	_soundPush = LoadSound("Res/Audio/AladdinPush.wav");
	_soundPantDrop = LoadSound("Res/Audio/Guard'sPants.wav");
	_soundHitted = LoadSound("Res/Audio/GuardHit1.wav");
	_soundGem = LoadSound("Res/Audio/GemCollect.wav");
	_soundTaunt = LoadSound("Res/Audio/GuardBeckon.wav");
	_soundThrow = LoadSound("Res/Audio/ObjectThrow.wav");

#pragma endregion
	if (_soundTheme == NULL)
		return 0;
	_soundTheme->Play(0, DSBPLAY_LOOPING);

	//Init components 


	_UI = new UIScene();
	mapinfo = new D3DXIMAGE_INFO();
	background = new Scene1BackGround();
	mapETC = LoadTexture("Res/map.png", D3DCOLOR_XRGB(63, 72, 204), mapinfo);

	mainCharacter = new Aladdin();
	mainCharacter->setAnchor(AnchorPoint::BOTTOM_MID);
	mainCharacter->setPosition(100, 400);
	MyCamera::GetInstance()->setPosition(100, 400);

	MyCamera::GetInstance()->setCurMapWidth(mapinfo->Width);
	MyCamera::GetInstance()->setCurMapHeight(mapinfo->Height);

	//mainCharacter->setLife(0);
	//MyCamera::GetInstance()->setPosition(MyCamera::GetInstance()->width() / 2, mapinfo->Height / 2 - MyCamera::GetInstance()->height() / 2);
	//return okay
	
	

	//Initiate trigger and shopper
	for (auto k = _gameObjectList->begin(); k != _gameObjectList->end(); k++)
	{
		tempTrigger = *k;
		if (tempTrigger->get_name() == "Trigger")
		{
			if (tempTrigger->x() < 2345)
				TriggerLeft = tempTrigger;

			if (tempTrigger->x() > 2345 && tempTrigger->x() < 3000)
				TriggerRight = tempTrigger;
		}
		if (tempTrigger->get_name() == "Shopper")
		{
			Shopper = tempTrigger;
		}
	}

	


	return 1;
}
void Scene1::NormalizeAction()
{
	if (mainCharacter->degree_state()!="3")
	{
		if (mainCharacter->on_state_end() == true)
			mainCharacter->set_on_state_end(false);
		mainCharacter->set_degree_state("0");
	}

}
void Scene1::Key_Pressed(int KeyCode)
{

	if ((gameCase != GAMECASES::PLAYING && gameCase != GAMECASES::CHOSING) || (gameCase == GAMECASES::PLAYING && mainCharacter->IsDying() == true) )
		return;

	switch (KeyCode)
	{
	case DIK_P:
		{
		mainCharacter->BeBeaten();
		break;
		}

	case DIK_A:
		NormalizeAction();
		mainCharacter->set_hand_state("2");
		_soundSlash->Play();
		break;
	case DIK_S:
		NormalizeAction();
	//	if (mainCharacter->is_throwing() == false)
		{
			mainCharacter->set_hand_state("1");
			mainCharacter->FireApple();
		}

		break;
	case DIK_D:
		NormalizeAction();
		if (mainCharacter->main_state() != "3" && mainCharacter->sub_state() == "0")
		{
			mainCharacter->set_sub_state("2");
			//mainCharacter->setIsRepeating(false);
			mainCharacter->setIsClimbing(false);
			mainCharacter->set_vy(JUMP_FORCE);
			mainCharacter->set_jump_step_remaining(JUMP_STEP);
			//mainCharacter->set_vy(JUMP_FORCE);
		}
		else
		{
			if (mainCharacter->sub_state() == "5")
				mainCharacter->setIsSwinging(false);
		}
		break;
	case DIK_LEFT:
		if (gameCase == GAMECASES::CHOSING)
		{
			mainCharacter->setState("100");
			Abu->set_state("2");
			gameCase = GAMECASES::QUIT; 
		}
		if (mainCharacter->main_state() == "4" && mainCharacter->curface() == GameObject::RIGHT)
		{
			mainCharacter->set_last_face(GameObject::RIGHT);
			mainCharacter->set_curFace(GameObject::LEFT);
			if(mainCharacter->CheckFlip() == true)
				mainCharacter->Flip();
		}
		break;
	case DIK_RIGHT:
		if (gameCase == GAMECASES::CHOSING)
		{
			mainCharacter->setState("100");
			Abu->set_state("2");
			gameCase = GAMECASES::CONTINUE; 
			if (Abu->CheckFlip() == true)
				Abu->Flip();
		}
		if (mainCharacter->main_state() == "4" && mainCharacter->curface() == GameObject::LEFT)
		{
			mainCharacter->set_last_face(GameObject::LEFT);
			mainCharacter->set_curFace(GameObject::RIGHT);
			if (mainCharacter->CheckFlip() == true)
				mainCharacter->Flip();
		}
		break;
	}
}

void Scene1::InputUpdate()
{
	 

	if (mainCharacter->degree_state() == "5" && mainCharacter->state_manager()->life_span() == 0)
	{
		mainCharacter->set_degree_state("0");
		mainCharacter->set_vx(0);
		mainCharacter->set_vy(0);
		mainCharacter->set_jump_step_remaining(0);
	}
		
	if (mainCharacter->degree_state() == "5")
		return;


	if ((gameCase != GAMECASES::PLAYING && gameCase != GAMECASES::CHOSING) || (gameCase == GAMECASES::PLAYING && mainCharacter->IsDying() == true))
		return;

	Poll_Keyboard();
	ProcessKeyboard();

	if (Key_Hold(DIK_UP))
	{
		NormalizeAction();
		if (mainCharacter->main_state() == "4")
		{
			mainCharacter->set_vy(-CHARACTER_VX/2);
			return;
		} 
		mainCharacter->set_main_state("2");
		mainCharacter->StopX();
		return; 
	};

	if (Key_Hold(DIK_DOWN))
	{

		NormalizeAction();
		if (mainCharacter->main_state() == "4")
		{
			mainCharacter->set_vy(CHARACTER_VX/2);
			return;
		}
		mainCharacter->StopX();
		mainCharacter->set_main_state("3");
		return;
	}

	if (Key_Hold(DIK_LEFT))
	{
		if (gameCase != GAMECASES::PLAYING)
		{
			return;
		}
		NormalizeAction();
		if (mainCharacter->main_state() != "4")
		{
			if (mainCharacter->on_state_end() == true)
				mainCharacter->set_on_state_end(false);
			mainCharacter->set_main_state("1");

			if (mainCharacter->main_state() == "1")
			{
				if (mainCharacter->on_state_end() == false)
					mainCharacter->set_prev_main_state("1");
			}
		}

		if (mainCharacter->isClimbing() == false)
			if (mainCharacter->isSwinging() == false)
				mainCharacter->set_vx(-CHARACTER_VX);
			else mainCharacter->set_vx(-CHARACTER_VX / 2);
		return;
	}
	if (Key_Hold(DIK_RIGHT))
	{
		if (gameCase != GAMECASES::PLAYING)
		{
			return;
		}
		NormalizeAction();
		if (mainCharacter->main_state() != "4")
		{
			if (mainCharacter->on_state_end() == true)
				mainCharacter->set_on_state_end(false);
			mainCharacter->set_main_state("1");
			if (mainCharacter->main_state() == "1")
			{
				if (mainCharacter->on_state_end() == false)
					mainCharacter->set_prev_main_state("1");
			}
		}

		if (mainCharacter->isClimbing() == false)
			if(mainCharacter->isSwinging()== false)
				mainCharacter->set_vx(CHARACTER_VX);
			else mainCharacter->set_vx(CHARACTER_VX/2);
		else
			mainCharacter->set_vx(0);
		return;
	}
	if (Key_Hold(DIK_D))
	{
		return;
	}

	//to edit later
	if (mainCharacter->main_state() != "4"
		|| (mainCharacter->main_state() == "4" && mainCharacter->isClimbing() == false))
	{
		mainCharacter->set_main_state("0");
	}
	if (mainCharacter->on_state_end() == false && mainCharacter->prev_main_state() == "1" && mainCharacter->hand_state() == "0" && mainCharacter->sub_state() == "0" && mainCharacter->vy() == 0 && mainCharacter->isClimbing() == false && mainCharacter->hand_state() == "0" && mainCharacter->isSwinging() == false)
	{
		mainCharacter->set_on_state_end(true);
		if (mainCharacter->degree_state() == "0")
		{
			mainCharacter->set_state("0001");
			mainCharacter->set_degree_state("1");
		}
		mainCharacter->set_prev_main_state("0");
	}
	if (mainCharacter->on_state_end() == true && mainCharacter->state_manager()->life_span() <= 0)
	{
		mainCharacter->set_on_state_end(false);
		mainCharacter->set_degree_state("0");
	}

	if (mainCharacter->main_state() == "4" && mainCharacter->isClimbing() == true)
		mainCharacter->StopY();
	if (mainCharacter->main_state() == "0" && mainCharacter->sub_state() == "5"  && mainCharacter->isSwinging() == true)
		mainCharacter->StopY();

	mainCharacter->StopX();

	return;
}
void Scene1::DisposablePhysicUpdate(float t)
{
	//burning handle
	//camel saliva
	if (find(_onScreenList->begin(), _onScreenList->end(), camel_saliva) != _onScreenList->end())
	{
		camel_saliva->setPosition(camel_saliva->x() + camel_saliva->vx()*t, camel_saliva->y() + camel_saliva->vy()*t);
		if (SimpleIntersect(&camel_target->bounding_box(), &camel_saliva->bounding_box()))
		{
			if (camel_target->is_immune() == 0.0f)
			{
				camel_target->set_health(camel_target->health() - 2);
				camel_target->set_is_immune(30);
				camel_target->set_state("003");
				camel_target->set_hand_state("3");
				camel_target->state_manager()->set_life_span(camel_target->state_manager()->getStateByCode("003").getListRect().size());
				camel_target->setIsRepeating(false);	
				camel_saliva->setVisible(false);
			}
		}
		
	}

	//handle surrounding
	for (auto i = listSpringBoard->begin(); i != listSpringBoard->end(); i++)
	{
		temp_object = *i;
		if (find(_onScreenList->begin(), _onScreenList->end(), temp_object) != _onScreenList->end())
		{
			if (temp_object->is_hitted() == true)
			{
				temp_object->set_state("001");
				temp_object->setIsRepeating(false);
			}
			if (temp_object->state_manager()->life_span() <= 0)
			{
				temp_object->set_state("000");
				temp_object->set_is_hitted(false);
				temp_object->setIsRepeating(true);
			}

		}


	}
	for (auto i = floatGroundList->begin(); i != floatGroundList->end(); i++)
	{
		temp_object = *i;

		if (temp_object->vy() != 0)
			temp_object->setPosition(temp_object->x(), temp_object->y() + temp_object->vy()*t);
		if (temp_object->y() >= 635)
		{
			temp_object->set_vy(0);
			temp_object->set_state("001");
		}
		if (temp_object->is_hitted() == true && temp_object->state_manager()->life_span() == 0)
		{
			temp_object->set_vy(temp_object->vy() + GRAVITY * 2);

		}
		if (temp_object->vy() == 0.0f && temp_object->is_hitted() == true && temp_object->y() != initFloatGroundList[distance(floatGroundList->begin(), i)].y)
			if (find(_onScreenList->begin(), _onScreenList->end(), temp_object) != _onScreenList->end())
			{
				temp_object->setPosition(initFloatGroundList[distance(floatGroundList->begin(), i)]);
				temp_object->set_is_hitted(false);
				temp_object->setIsRepeating(true);
				temp_object->set_state("000");
			}

	}
	for (auto i = pot_list->begin(); i != pot_list->end();)
	{
		temp_pot_bullet = *i;
		if (find(_onScreenList->begin(), _onScreenList->end(), temp_pot_bullet) == _onScreenList->end())
		{
			delete *i;
			i = pot_list->erase(i);
			_gameObjectList->remove(temp_pot_bullet);
			PlaySound(_soundPotFall);
		}
		else
		{

			if (temp_pot_bullet->y() >= temp_pot_bullet->break_point())
			{
				temp_pot_bullet->set_vy(0);
				temp_pot_bullet->set_is_hitted(true);
				temp_pot_bullet->set_state("001");
				temp_pot_bullet->setIsRepeating(false);
				if (temp_pot_bullet->state_manager()->life_span() == 0)
					_gameObjectList->remove(temp_pot_bullet);
				
			}
			else temp_pot_bullet->set_vy(temp_pot_bullet->vy() + 1);
			temp_pot_bullet->setPosition(temp_pot_bullet->x() + temp_pot_bullet->vx()*t, temp_pot_bullet->y() + temp_pot_bullet->vy()*t);


			if (SimpleIntersect(&mainCharacter->bounding_box(), &temp_pot_bullet->bounding_box()) && temp_pot_bullet->is_hitted()==false)
			{
				mainCharacter->BeBeaten();
			}
			i++;
		}
	}
		

		
	for (auto i = _disposableList->begin(); i != _disposableList->end();)
	{
		temp_bullet_enemy = *i;
		if (find(_onScreenList->begin(), _onScreenList->end(), temp_bullet_enemy) == _onScreenList->end())
		{
			//OutputDebugString(std::to_string(reinterpret_cast<int>(*i)).c_str());
			delete *i;
			i = _disposableList->erase(i);
			_gameObjectList->remove(temp_bullet_enemy);
		}
		else
		{
			_bulletCollide = &CheckCollision(temp_bullet_enemy, mainCharacter);
			switch (mapIdName[temp_bullet_enemy->get_name()])
			{
			case 16:
				//parabol knife
				if (temp_bullet_enemy->isKnifeHitted == false)
				{
					if (temp_object_jug->curface() == GameObject::RIGHT)
						temp_bullet_enemy->set_vx(BULLET_PREFAB_VX);
					else
						temp_bullet_enemy->set_vx(-BULLET_PREFAB_VX);
				}
				// Max_x : so duong , Max_y : so am
				if(temp_bullet_enemy->isKnifeHitted == false)
					temp_bullet_enemy->set_vy(CalculateParabolVy(temp_bullet_enemy->vx(), temp_object_jug->Position(), 150, -150, temp_bullet_enemy->x()));
				else
					temp_bullet_enemy->set_vy(CalculateParabolVy(temp_bullet_enemy->vx()*1.5f, hittedPosition, abs(hittedPosition.x - temp_object_jug->x() - 6) , -abs(hittedPosition.y - temp_object_jug->y()) , temp_bullet_enemy->x()));
				break;

			}
			//to remove disposable thing out of screen when they are out of sight
			temp_bullet_enemy->setPosition(temp_bullet_enemy->x() + temp_bullet_enemy->vx()*t, temp_bullet_enemy->y() + temp_bullet_enemy->vy()*t);

			if (_bulletCollide->_collisionIndex == 0.0f && mainCharacter->is_immune() == 0.0f)
			{
				mainCharacter->BeBeaten();
			}

			
			if (SimpleIntersect(mainCharacter->sword(), &temp_bullet_enemy->bounding_box()))
			{
				temp_bullet_enemy->set_vx(-temp_bullet_enemy->vx());
				if (temp_bullet_enemy->get_name() == "ParabolKnife")
				{
					temp_bullet_enemy->isKnifeHitted = true;
					if(mainCharacter->curface() == RIGHT)
						hittedPosition.x = mainCharacter->sword()->right;
					else
						hittedPosition.x = mainCharacter->sword()->left;
					hittedPosition.y = mainCharacter->sword()->top;

				}
				else
					temp_bullet_enemy->set_vy(-temp_bullet_enemy->vy());
			}
				
			i++;
		}

	}
}
void Scene1::EnemyThinAI(GameObjectMove* obj_mov)
{
	if (obj_mov->hand_state() != "3" || (obj_mov->hand_state() == "3"&& obj_mov->state_manager()->life_span() == 0))
	{
		if (obj_mov->state_manager()->life_span() == 0)
			obj_mov->set_state("000");
		if (abs(obj_mov->x() - mainCharacter->x())<150)
		{
			if (abs(obj_mov->x() - mainCharacter->x())<40)
			{
				obj_mov->setIsRepeating(false);
				obj_mov->set_state("002");
				obj_mov->set_hand_state("2");
				obj_mov->set_vx(0);
				if (obj_mov->hand_state() == "2" && obj_mov->state_manager()->life_span() == 0)
				{
					obj_mov->set_state("000");
					obj_mov->set_state("002");
				}
				return;
			}
			else
			{
				if (obj_mov->reach_limit() == false)
				{
					obj_mov->setIsRepeating(true);
					obj_mov->set_state("001");
					obj_mov->set_hand_state("1");
					obj_mov->set_vx((obj_mov->curface() == GameObject::RIGHT) ? 5 : -5);
					return;
				}
				else
				{
					obj_mov->setIsRepeating(true);
					obj_mov->set_state("000");
					obj_mov->set_hand_state("0");
					return;
				}

			}
		}
	}


}
void Scene1::EnemyMusAI(GameObjectMove* obj_mov)
{
	if (obj_mov->hand_state() != "3" || (obj_mov->hand_state() == "3" && obj_mov->state_manager()->life_span() == 0))
	{
		if (obj_mov->state_manager()->life_span() == 0)
			obj_mov->set_state("000");
		if (obj_mov->hand_state() == "3" && obj_mov->state_manager()->life_span() == 0)
			obj_mov->setIsRepeating(true);
		//if in range of sight, muscle will attack
		if (abs(mainCharacter->x() - obj_mov->x())<70)
		{
			for (list<GameObject*>::iterator it = listFireGround->begin(); it != listFireGround->end(); it++)
			{
				tempFireGround = *it;
				if (find(_onScreenList->begin(), _onScreenList->end(), tempFireGround) != _onScreenList->end())
				{
					if (SimpleIntersect(&tempFireGround->bounding_box(), &obj_mov->bounding_box()))
					{
						obj_mov->set_state("004");
						obj_mov->set_hand_state("4");
						obj_mov->setIsRepeating(true);
						return;
					}
				}

			}
			//if (obj_mov->reach_limit() == true)
			//{
			//	obj_mov->setIsRepeating(true);
			//	obj_mov->set_state("000");
			//	obj_mov->set_hand_state("0");
			//}

			if (obj_mov->hand_state() == "0" || obj_mov->hand_state() == "1")
			{
				obj_mov->set_state("002");
				obj_mov->set_is_stand_still(true);
				obj_mov->set_hand_state("2");
				obj_mov->setIsRepeating(false);
				obj_mov->set_vx(0);
			}
			if (obj_mov->hand_state() == "2" || (obj_mov->hand_state() == "5"&&obj_mov->state_manager()->life_span() == 0))
			{
				if (obj_mov->state_manager()->life_span() == 0 && obj_mov->attack_turn_remain() != 0)
				{
					obj_mov->set_attack_turn_remain(obj_mov->attack_turn_remain() - 1);
					obj_mov->set_state("000");
					obj_mov->set_state("002");
					PlaySound(_soundHighSword);
					obj_mov->set_is_stand_still(true);
					obj_mov->set_hand_state("2");
					obj_mov->setIsRepeating(false);
					obj_mov->set_vx(0);
				}
			}
			if (obj_mov->attack_turn_remain() == 0)
			{
				obj_mov->set_attack_turn_remain(3);
				obj_mov->set_state("005");
				PlaySound(_soundLowSword);
				obj_mov->set_is_stand_still(true);
				obj_mov->set_hand_state("5");
				obj_mov->setIsRepeating(false);
				obj_mov->set_vx(0);
			}
			return;
		}
		//if in range of sight, mus will taunt
		else
		{

			//if in range of pursuit, muscle will pursue
			if (abs(mainCharacter->x() - obj_mov->x()) < 90 && obj_mov->reach_limit() == false)
			{
				if (abs(mainCharacter->x() - obj_mov->x()) < 150)
				{
					if (obj_mov->is_stand_still() == false && obj_mov->reach_limit() == false)
					{
						obj_mov->setIsRepeating(true);
						obj_mov->set_state("001");
						obj_mov->set_hand_state("1");
						obj_mov->set_vx((obj_mov->curface() == GameObject::RIGHT) ? 5 : -5);
						obj_mov->set_played_sound_taunt(false);
					}
					return;
				}
				obj_mov->setIsRepeating(true);
				obj_mov->set_state("000");
				obj_mov->set_hand_state("0");

				return;
			}

		}
		if (obj_mov->reach_limit() == true)
		{
			obj_mov->setIsRepeating(true);
			obj_mov->set_state("000");
			if(obj_mov->played_sound_taunt()==false)
			{
				obj_mov->set_played_sound_taunt(true);
				PlaySound(_soundTaunt);
			}
				
			obj_mov->set_hand_state("0");
			return;
		}

	}
}
void Scene1::EnemyFatAI(GameObjectMove* obj_mov)
{
	if (obj_mov->hand_state() != "3" || (obj_mov->hand_state() == "3" && obj_mov->state_manager()->life_span() == 0))
	{
		obj_mov->setIsRepeating(true);
		if (obj_mov->reach_limit() == true)
		{
			if (obj_mov->hand_state() != "2" || ((obj_mov->state_manager()->life_span() <= 0) && (obj_mov->hand_state() != "2")))
			{
				obj_mov->setIsRepeating(true);
				obj_mov->set_is_stand_still(true);
				obj_mov->set_state("000");
				obj_mov->set_hand_state("0");
				obj_mov->set_attack_turn_remain(4);
			}

			if (abs(mainCharacter->x() - obj_mov->x())<80 && obj_mov->is_throwing() == false && obj_mov->attack_turn_remain() != 0)
			{
				obj_mov->set_state("002");
				obj_mov->set_is_stand_still(true);
				obj_mov->set_hand_state("2");
				obj_mov->setIsRepeating(false);
				if (obj_mov->hand_state() == "2" && obj_mov->state_manager()->life_span() == 3)
				{
					obj_mov->set_attack_turn_remain(obj_mov->attack_turn_remain() - 1);
					GameObject* temp_bullet = new GameObject();
					D3DXVECTOR3 temp_pos = (obj_mov->curface() == GameObject::RIGHT) ? obj_mov->CalPositon(MID_RIGHT) : obj_mov->CalPositon(MID_LEFT);
					
					BulletPrefab::Instantiate(temp_bullet, "Knife", temp_pos.x, temp_pos.y - 10, obj_mov->curface());
					if (mainCharacter->y() + 10 < obj_mov->y())
						temp_bullet->set_vy(-5);
					else temp_bullet->set_vy(5);
					temp_bullet->set_name("StraightKnife");
					

					_onScreenList->remove(obj_mov->weapon_obj());
					_disposableList->remove(obj_mov->weapon_obj());
					_gameObjectList->remove(obj_mov->weapon_obj());
					obj_mov->set_weapon_obj(temp_bullet);
					_disposableList->push_back(temp_bullet);
					_gameObjectList->push_back(temp_bullet);
					_onScreenList->push_back(temp_bullet);
					obj_mov->set_is_throwing(true);
				}

			}
		}
		else
		{
			if (obj_mov->vx() == 0 && obj_mov->attack_turn_remain() == 0)
			{
				obj_mov->set_is_stand_still(true);
				obj_mov->setIsRepeating(true);
				obj_mov->set_state("000");
				obj_mov->set_hand_state("0");
				obj_mov->set_attack_turn_remain(4);
			}
			//if in range of sight, fat will attack
			if (abs(mainCharacter->x() - obj_mov->x())<80 && obj_mov->is_throwing() == false && obj_mov->attack_turn_remain() != 0)
			{
				obj_mov->set_state("002");
				obj_mov->set_is_stand_still(true);
				obj_mov->set_hand_state("2");
				obj_mov->setIsRepeating(false);
				obj_mov->set_vx(0);
				if (obj_mov->hand_state() == "2" && obj_mov->state_manager()->life_span() == 3)
				{
					obj_mov->set_attack_turn_remain(obj_mov->attack_turn_remain() - 1);
					GameObject* temp_bullet = new GameObject();
					D3DXVECTOR3 temp_pos = (obj_mov->curface() == GameObject::RIGHT) ? obj_mov->CalPositon(MID_RIGHT) : obj_mov->CalPositon(MID_LEFT);

					BulletPrefab::Instantiate(temp_bullet, "Knife", temp_pos.x, temp_pos.y - 10, obj_mov->curface());
					if (mainCharacter->y() + 10 < obj_mov->y())
						temp_bullet->set_vy(-3);
					else temp_bullet->set_vy(3);
					
					temp_bullet->set_name("StraightKnife");

					_onScreenList->remove(obj_mov->weapon_obj());
					_disposableList->remove(obj_mov->weapon_obj());
					_gameObjectList->remove(obj_mov->weapon_obj());
					obj_mov->set_weapon_obj(temp_bullet);
					_disposableList->push_back(temp_bullet);
					_gameObjectList->push_back(temp_bullet);
					_onScreenList->push_back(temp_bullet);
					obj_mov->set_is_throwing(true);
				}
			}
			else
				//if in range of pursuit, fat will pursue
				if (abs(mainCharacter->x() - obj_mov->x()) < 150)
				{
					if ((obj_mov->is_stand_still() == false || (obj_mov->vx() != 0)) && obj_mov->reach_limit() == false && obj_mov->is_throwing() == false)
					{
						obj_mov->setIsRepeating(true);
						obj_mov->set_vx((obj_mov->curface() == GameObject::RIGHT) ? 5 : -5);
						obj_mov->set_state("001");
						obj_mov->set_hand_state("1");
					}
				}
			if (obj_mov->hand_state() == "2" && obj_mov->is_throwing() == true)
			{
				if (obj_mov->hand_state() == "2" && obj_mov->state_manager()->life_span() == 3)
				{
					obj_mov->set_attack_turn_remain(obj_mov->attack_turn_remain() - 1);
					GameObject* temp_bullet = new GameObject();
					D3DXVECTOR3 temp_pos = (obj_mov->curface() == GameObject::RIGHT) ? obj_mov->CalPositon(MID_RIGHT) : obj_mov->CalPositon(MID_LEFT);
					
					BulletPrefab::Instantiate(temp_bullet, "Knife", temp_pos.x, temp_pos.y - 10, obj_mov->curface());
					if (mainCharacter->y() + 20 < obj_mov->y())
						temp_bullet->set_vy(-3);
					else temp_bullet->set_vy(3);
					temp_bullet->set_name("StraightKnife");

					_onScreenList->remove(obj_mov->weapon_obj());
					_disposableList->remove(obj_mov->weapon_obj());
					_gameObjectList->remove(obj_mov->weapon_obj());
					obj_mov->set_weapon_obj(temp_bullet);
					
					_disposableList->push_back(temp_bullet);
					_gameObjectList->push_back(temp_bullet);
					_onScreenList->push_back(temp_bullet);
					obj_mov->set_is_throwing(true);
				}
				obj_mov->setIsRepeating(true);
				obj_mov->set_state("000");
				obj_mov->set_hand_state("0");
				obj_mov->set_is_stand_still(true);

			}
		}


	}
}
void Scene1::EnemyJugAI(GameObjectMove* obj_mov)
{
	temp_object_jug = obj_mov;

	obj_mov->setIsRepeating(true);
	obj_mov->set_state("000");
	obj_mov->set_is_stand_still(true);

	if (abs(obj_mov->x() - mainCharacter->x())>120 && obj_mov->is_throwing() == false)
	{

		if (obj_mov->is_throwing() == false)
		{
			GameObject* temp_bullet = new GameObject();
			D3DXVECTOR3 temp_pos = (obj_mov->curface() == GameObject::RIGHT) ? obj_mov->CalPositon(TOP_RIGHT) : obj_mov->CalPositon(TOP_LEFT);
			BulletPrefab::Instantiate(temp_bullet, "Knife", temp_pos.x, temp_pos.y, obj_mov->curface());
			temp_bullet->set_name("ParabolKnife");
		
			_onScreenList->remove(obj_mov->weapon_obj());
			_disposableList->remove(obj_mov->weapon_obj());
			_gameObjectList->remove(obj_mov->weapon_obj());
			obj_mov->set_weapon_obj(temp_bullet);
			_disposableList->push_back(temp_bullet);
			_gameObjectList->push_back(temp_bullet);
			_onScreenList->push_back(temp_bullet);
			obj_mov->set_is_throwing(true);
		}
		return;
	}
	else
	{
	
			if (obj_mov->is_throwing() == false)
			{
				obj_mov->set_attack_turn_remain(obj_mov->attack_turn_remain() - 1);
				GameObject* temp_bullet = new GameObject();
				D3DXVECTOR3 temp_pos = (obj_mov->curface() == GameObject::RIGHT) ? obj_mov->CalPositon(MID_RIGHT) : obj_mov->CalPositon(MID_LEFT);

				BulletPrefab::Instantiate(temp_bullet, "Knife", temp_pos.x, temp_pos.y - 10, obj_mov->curface());
				if (mainCharacter->y() + 20 < obj_mov->y())
					temp_bullet->set_vy(-2);
				else temp_bullet->set_vy(2);
				
				temp_bullet->set_name("StraightKnife");
				_onScreenList->remove(obj_mov->weapon_obj());
				_disposableList->remove(obj_mov->weapon_obj());
				_gameObjectList->remove(obj_mov->weapon_obj());
				obj_mov->set_weapon_obj(temp_bullet);
				_disposableList->push_back(temp_bullet);
				_gameObjectList->push_back(temp_bullet);
				_onScreenList->push_back(temp_bullet);
				obj_mov->set_is_throwing(true);
			}
		
	}


}
void Scene1::EnemyJarAI(GameObjectMove* obj_mov)
{
	if (obj_mov->hand_state() != "3" || (obj_mov->hand_state() == "3"&& obj_mov->state_manager()->life_span() == 0))
	{

		if (abs(obj_mov->x() - mainCharacter->x())<100)
		{
			if (abs(obj_mov->x() - mainCharacter->x())<40)
			{
				obj_mov->setIsRepeating(false);
				obj_mov->set_state("002");
				obj_mov->set_hand_state("2");
				obj_mov->set_vx(0);
				if (obj_mov->hand_state() == "2" && obj_mov->state_manager()->life_span() == 0)
				{
					obj_mov->set_state("000");
					obj_mov->set_state("002");
					if (SimpleIntersect(&mainCharacter->bounding_box(), &obj_mov->bounding_box()))
						if(mainCharacter->is_immune() == 0.0f)
						{
							if (mainCharacter->appleCount() >= 3)
								mainCharacter->setAppleCount(mainCharacter->appleCount() - 3);
							else mainCharacter->setAppleCount(0);
						}
				}
				return;
			}
			else
			{
				if (obj_mov->reach_limit() == false)
				{
					obj_mov->setIsRepeating(true);
					obj_mov->set_state("001");
					obj_mov->set_hand_state("1");
					obj_mov->set_vx((obj_mov->curface() == GameObject::RIGHT) ? 5 : -5);
					return;
				}
				else
				{
					obj_mov->setIsRepeating(false);
					obj_mov->set_state("000");
					obj_mov->set_hand_state("0");
					return;
				}

			}
		}
	}

}
void Scene1::EnemyHandAI(GameObjectMove* obj_mov)
{
	if (abs(obj_mov->x() - mainCharacter->x())< 80)
	{
		if (obj_mov->is_throwing() == false)
		{
			obj_mov->set_state("001");
			obj_mov->set_hand_state("1");
			obj_mov->setIsRepeating(false);
			if (obj_mov->hand_state() == "1" && obj_mov->state_manager()->life_span() == 3)
			{
				Pot* temp_pot = new Pot();
				PotPrefab::Instantiate(temp_pot, obj_mov->x(), obj_mov->y(), obj_mov->max_x());
				_onScreenList->remove(obj_mov->weapon_obj());
				_disposableList->remove(obj_mov->weapon_obj());
				_gameObjectList->remove(obj_mov->weapon_obj());
				obj_mov->set_weapon_obj(temp_pot);
				pot_list->push_back(temp_pot);
				_gameObjectList->push_back(temp_pot);
				_onScreenList->push_back(temp_pot);
				obj_mov->set_is_throwing(true);
			}
		}
		if (obj_mov->is_throwing() == true && obj_mov->state_manager()->life_span() == 0)
		{
			obj_mov->set_state("000");
			obj_mov->set_hand_state("0");
			obj_mov->setIsRepeating(true);
		}
	}
	else
	{
		if (obj_mov->is_throwing() == false)
		{
			obj_mov->set_state("000");
			obj_mov->set_hand_state("0");
			obj_mov->setIsRepeating(true);
		}
	}
}
void Scene1::EnemyHandle(float t)
{
	//handle physic of all enemies

	for (auto i = _healthHavingList->begin(); i != _healthHavingList->end();i++)
	{
		
		temp_object_move = *i;
		if (temp_object_move->Visbile() == false)
			continue;
		//handle when they are dead
		if (temp_object_move->health() == 0 && temp_object_move->Visbile()==true)
		{
			_explosion->setPosition(temp_object_move->Position());
			//delete *i;
			//i = _healthHavingList->erase(i);
			temp_object_move->setVisible(false);

			//_gameObjectList->remove(temp_object_move);
			//_onScreenList->remove(temp_object_move);
			_explosion->state_manager()->setState("000");
			_explosion->Reset();
			_explosion->setVisible(true);
			_explosion->setIsRepeating(false);
			//trace(L"%f %f", _explosion->x(), _explosion->y());
			//_gameObjectList->push_back(_explosion);
			_onScreenList->push_back(_explosion);
		}
		else
		{
			if (std::find(_onScreenList->begin(), _onScreenList->end(), (GameObject*)*i) != _onScreenList->end())
			{




				if (std::find(_onScreenList->begin(), _onScreenList->end(), temp_object_move->weapon_obj()) == _onScreenList->end())
					temp_object_move->set_is_throwing(false);
				if (mainCharacter->x() < temp_object_move->x())
					temp_object_move->set_curFace(GameObject::LEFT);
				else temp_object_move->set_curFace(GameObject::RIGHT);
				if (temp_object_move->CheckFlip() && temp_object_move->get_name()!="EnemyHand")
				{
					temp_object_move->set_vx(-temp_object_move->vx());
					temp_object_move->Flip();

				}


				//handle their state and movement
				//if (temp_object_move->vx() != 0 && temp_object_move->health() > 0)
				//{
				//	temp_object_move->set_state("001");
				//}
				temp_object_move->set_distance_from_main(abs(mainCharacter->x() - temp_object_move->x()));
				temp_object_move->PhysicUpdate(t);
				switch (mapIdName[temp_object_move->get_name()])
				{
				case 11:
					EnemyThinAI(temp_object_move);
					break;
				case 12:
					EnemyMusAI(temp_object_move);
					break;
				case 13:
					EnemyFatAI(temp_object_move);
					break;
				case 14:
					EnemyJugAI(temp_object_move);
					break;
				case 15:
					EnemyJarAI(temp_object_move);
					break;
				case 20:
					EnemyHandAI(temp_object_move);
					break;



				}
			}
			//i++;
		}
	}
}
void Scene1::CollisionDetect()
{
	Quadtree* quadtree = Quadtree::CreateQuadtree(MyCamera::GetInstance()->bounding_box().left, MyCamera::GetInstance()->bounding_box().top, MyCamera::GetInstance()->bounding_box().right, MyCamera::GetInstance()->bounding_box().bottom);

	std::list<GameObject*>* return_object_list = new std::list<GameObject*>();
	quadtree->Retrieve(return_object_list, MyCamera::GetInstance());
	for (auto x = return_object_list->begin(); x != return_object_list->end(); x++)
	{
		temp_object = *x;
		if (temp_object->Visbile() == true)
		{
			mainCharacter->set_bounding_box(CalculateBoundingBox(mainCharacter->x(), mainCharacter->y(), mainCharacter->width(), mainCharacter->height(), mainCharacter->anchor()));
			temp_object->set_bounding_box(CalculateBoundingBox(temp_object->x(), temp_object->y(), temp_object->width(), temp_object->height(), temp_object->anchor()));


			CollisionResult collisionResult = CheckCollision(mainCharacter, temp_object);


			if (collisionResult._collisionIndex < 1 && collisionResult._collisionIndex >= 0)
			{
				//MainCharacter collision with others z
				int collisionNameID = mapIdName[temp_object->get_name()];
				switch (collisionNameID)
				{
				case 47:
					
						if (mainCharacter->sub_state() =="2")
							mainCharacter->set_vy(5);
						break;

				case 0://Apple
					if (temp_object->IsDisappearing() == false)
					{
						_itemsList->push_back(temp_object);

						mainCharacter->setAppleCount(mainCharacter->appleCount() + 1);
						//sound
						if (_soundCollectApple->IsSoundPlaying() == false)
							_soundCollectApple->Play();
						temp_object->set_state("1");
						temp_object->setDisappearing(true);
					}
					
					break;
				case 19://FireGround
					if (collisionResult._collisionSide == LEFT || collisionResult._collisionSide == RIGHT)
					{
						mainCharacter->set_vy(-2);
					}
					if (collisionResult._collisionSide == UPTOP)
					{
						mainCharacter->set_vy((collisionResult._collisionIndex*mainCharacter->vy()));
					}
					if (find(_gameObjectList->begin(), _gameObjectList->end(), temp_burnfx) == _gameObjectList->end())
					{
						//temp_burnfx->setPosition(mainCharacter->x(), mainCharacter->y());
						//temp_burnfx->set_state("001");

						_gameObjectList->push_back(temp_burnfx);
						PlaySound(_soundFire);
						//if (find(_onScreenList->begin(), _onScreenList->end(), temp_burnfx) == _onScreenList->end())
						//	_onScreenList->push_back(temp_burnfx);
					}
					temp_burnfx->setPosition(mainCharacter->x(), mainCharacter->y());
					temp_burnfx->set_state("001");
					temp_burnfx->setVisible(true);
					temp_burnfx->setIsRepeating(true);
					if (find(_onScreenList->begin(), _onScreenList->end(), temp_burnfx) == _onScreenList->end())
						_onScreenList->push_back(temp_burnfx);
					if (mainCharacter->vx() == 0)
						mainCharacter->BeBeaten();
					break;

				case 1://Ground

					if (collisionResult._collisionSide == DOWNBOTTOM)
					{
						mainCharacter->set_vy(-collisionResult._collisionIndex*mainCharacter->vy());
					}
					if (collisionResult._collisionSide == UPTOP)
					{
						mainCharacter->set_vy((collisionResult._collisionIndex*mainCharacter->vy()));
					}
					if (collisionResult._collisionIndex == 0.0f)
					{
						if (collisionResult._collisionSide == UPTOP)
						{
							if (mainCharacter->sub_state() == "1" && mainCharacter->state_manager()->life_span() == 3)
							{
								mainCharacter->set_on_state_end(true);
								mainCharacter->set_state("0002");
								mainCharacter->set_degree_state("2");
							}
						}
						if ((mainCharacter->curface() == GameObject::RIGHT) && collisionResult._collisionSide == Side::LEFT && mainCharacter->vx()>0)
						{
							mainCharacter->set_vx(0);
						}
						if ((mainCharacter->curface() == GameObject::LEFT) && collisionResult._collisionSide == Side::RIGHT && mainCharacter->vx()<0)
						{
							mainCharacter->set_vx(0);
						}
						temp_burnfx->setVisible(false);
					}
					break;
				case 2: //Wall 
					if (collisionResult._collisionSide == UPTOP)
					{
						mainCharacter->set_vy((collisionResult._collisionIndex*mainCharacter->vy()));
						break;
					}
					if (collisionResult._collisionSide == NONE)//|| collisionResult._collisionSide == LEFT || collisionResult._collisionSide == RIGHT)
					{
						float newXPosition = mainCharacter->x();
						if (mainCharacter->curface() == GameObject::RIGHT)
						{
							mainCharacter->set_FacePush(GameObject::RIGHT);
							if (mainCharacter->CurrentState() == "Push")
							{
								int nextWidth = mainCharacter->state_manager()->curState().MaxBounding().right - mainCharacter->state_manager()->curState().MaxBounding().left;
								newXPosition = temp_object->bounding_box().left - nextWidth / 2 - CHARACTER_VX*FIXED_TIME;
							}
							else
							{
								//newXPosition = temp_object->bounding_box().left - 21;
								int nextWidth = mainCharacter->state_manager()->curState().MaxBounding().right - mainCharacter->state_manager()->curState().MaxBounding().left;
								newXPosition = temp_object->bounding_box().left - nextWidth / 2 - CHARACTER_VX*FIXED_TIME;
							}
						}
						else
						{
							mainCharacter->set_FacePush(GameObject::LEFT);
							if (mainCharacter->CurrentState() == "Push")
							{
								int nextWidth = mainCharacter->state_manager()->curState().MaxBounding().right - mainCharacter->state_manager()->curState().MaxBounding().left;
								newXPosition = temp_object->bounding_box().right + nextWidth / 2 + CHARACTER_VX*FIXED_TIME;
							}
							else
							{
								//	newXPosition = temp_object->bounding_box().right + 21;
								int nextWidth = mainCharacter->state_manager()->curState().MaxBounding().right - mainCharacter->state_manager()->curState().MaxBounding().left;
								newXPosition = temp_object->bounding_box().right + nextWidth / 2 + CHARACTER_VX*FIXED_TIME;
							}
						}
						mainCharacter->setPosition(newXPosition, mainCharacter->y());
						MyCamera::GetInstance()->setPosition(newXPosition, mainCharacter->y());
						break;
					}
					mainCharacter->set_vx(0);
					if (mainCharacter->sub_state()=="0")
					{
						mainCharacter->set_sub_state("3");
						if (_soundPush->IsSoundPlaying() == false)
							PlaySound(_soundPush);
					}
						
					//if (mainCharacter->vx() != 0 && mainCharacter->sub_state() != "1" && mainCharacter->sub_state() != "2")
					break;

				case 3://Rope
					if (mainCharacter->isSwinging())
						break;

					if ((mainCharacter->sub_state() == "1" ||
						mainCharacter->isClimbing() == true) &&
						collisionResult._collisionIndex == 0.0f)
					{
						mainCharacter->setIsClimbing(true);
						if (mainCharacter->bounding_box().top >= temp_object->bounding_box().top)
						{
							mainCharacter->setPosition(temp_object->x(), mainCharacter->y());
							//mainCharacter->set_sub_state("1");
						}
						else
						{
							if (mainCharacter->vy() < 0)
								mainCharacter->set_vy(0);
							mainCharacter->set_sub_state("1");
						}
						mainCharacter->set_vx(0);
						mainCharacter->set_main_state("4");
						temp_burnfx->setVisible(false);
						//MyCamera::GetInstance()->setPosition(temp_object->x(), MyCamera::GetInstance()->y());
					}

					break;
				case 4://HorizontalBar
				{
					if (mainCharacter->sub_state() == "1"
						|| mainCharacter->sub_state() == "2"
						|| mainCharacter->isSwinging() == true)
					{
						mainCharacter->StopY();
						string str;
						str = mainCharacter->main_state() + "7" + mainCharacter->hand_state();


						mainCharacter->setIsSwinging(true);
						int height;

						//OutputDebugString("\n");
						//OutputDebugString(str.c_str());
						height = mainCharacter->state_manager()->getStateByCode(str).getListRect().at(0).bottom - mainCharacter->state_manager()->getStateByCode(str).getListRect().at(0).top;
						//OutputDebugString(("  : " + to_string(height)).c_str());
						if (mainCharacter->bounding_box().left >= temp_object->bounding_box().left
							&& mainCharacter->bounding_box().right <= temp_object->bounding_box().right)
						{
							mainCharacter->setPosition(mainCharacter->x(), temp_object->CalPositon(TOP_LEFT).y + height - 5);
						}
						if (mainCharacter->bounding_box().left < temp_object->bounding_box().left && mainCharacter->vx() < 0)
						{
							mainCharacter->StopX();
							mainCharacter->setPosition(temp_object->CalPositon(TOP_LEFT).x + mainCharacter->width() / 2, temp_object->CalPositon(TOP_LEFT).y + height);
						}
						if (mainCharacter->bounding_box().right > temp_object->bounding_box().right && mainCharacter->vx() > 0)
						{

							mainCharacter->StopX();
							mainCharacter->setPosition(temp_object->CalPositon(TOP_RIGHT).x - mainCharacter->width() / 2, temp_object->CalPositon(TOP_LEFT).y + height);
						}
						mainCharacter->set_sub_state("5");
						//mainCharacter->set_sub_state("1");
					}
					//MyCamera::GetInstance()->setPosition(temp_object->x(), MyCamera::GetInstance()->y());

					//mainCharacter->set_main_state("0");
				}
				break;
				case 30://Shopper

					if (temp_object->state_manager()->curState().getName() == "Idle1")
					{
						temp_object->setIsRepeating(false);
						temp_object->set_state("3");
						temp_object->Reset();
					}


					if ((Shopper->state_manager()->curState().getName() == "ShopperOpen"
						|| Shopper->state_manager()->curState().getName() == "Idle3")
						&& Shopper->state_manager()->life_span() == 0
						)
					{
						Shopper->set_state("1"); 
					}
					if (Shopper->state_manager()->curState().getName() == "Idle2" && Shopper->state_manager()->life_span() == 0)
					{
						Shopper->set_state("2");
					}

					if (mainCharacter->CurrentState() == "IdleUp" && collisionResult._collisionSide == NONE && mainCharacter->state_manager()->life_span() == 2
						&& ShopperText->Visbile() == false && ShopperText->curface() == GameObject::RIGHT
						&& (Shopper->state_manager()->curState().getName()=="Idle2" || Shopper->state_manager()->curState().getName() == "Idle2") 
						)
					{

						if ((mainCharacter->bounding_box().right < 3920 && mainCharacter->DiamondCount() < 5)
							|| (mainCharacter->bounding_box().left >= 3920 && mainCharacter->DiamondCount() < 10))
						{
							ShopperText->set_state("0");
							ShopperText->setVisible(true);
						}
						if (mainCharacter->bounding_box().right < 3920 && mainCharacter->DiamondCount() >= 5)
						{
							mainCharacter->setDiamondCount(mainCharacter->DiamondCount() - 5);
							mainCharacter->setLife(mainCharacter->Life() + 1);
							ShopperText->set_state("1");
							ShopperText->setVisible(true);
						}

						if (mainCharacter->bounding_box().left >= 3920 && mainCharacter->DiamondCount() >= 10)
						{
							mainCharacter->setDiamondCount(mainCharacter->DiamondCount() - 10);
							ShopperText->set_state("1");
							ShopperText->setVisible(true);
						}
						ShopperText->setPosition(MyCamera::GetInstance()->x(), ShopperText->y());
					}
					if (mainCharacter->vx() != 0 && ShopperText->Visbile() == true)
					{
						if (ShopperText->state_manager()->curState().getName() == "FindMore")
							ShopperText->set_state("2");
						if (ShopperText->state_manager()->curState().getName() == "MakeDeal")
							ShopperText->set_state("3");
						ShopperText->set_curFace(GameObject::LEFT);
					}
					break;
				case 31://Trigger  
					if (temp_object->x() > 2345 && temp_object->x() < 3000)
					{
						if (collisionResult._collisionSide == LEFT)
						{
							mainCharacter->set_ChosenLayer(1);
						}
					}

					if (temp_object->x() < 2345)
					{
						if (mainCharacter->vx() < 0)
						{
							if (mainCharacter->ChosenLayer() == 1 && TriggerLeft->Visbile() == true)
							{
								TriggerLeft->setVisible(false);
								mainCharacter->set_ChosenLayer(2);
							}
							if (mainCharacter->ChosenLayer() == 2 && TriggerLeft->Visbile() == true)
							{
								TriggerLeft->setVisible(false);
								mainCharacter->set_ChosenLayer(1);
							}
						}
					}

					temp_object->setAnimaDelay(4);

					if (temp_object->x() > 3000 && temp_object->x() < 4000)
					{
						//OutputDebugString("Lifespan");
						//	OutputDebugString(to_string(Shopper->state_manager()->life_span()).c_str());
						if ((Shopper->state_manager()->curState().getName() == "ShopperOpen"
							|| Shopper->state_manager()->curState().getName() == "Idle3")
							&& Shopper->state_manager()->life_span() == 0
							)
						{
							Shopper->set_state("1");

						}
						if (Shopper->state_manager()->curState().getName() == "Idle2" && Shopper->state_manager()->life_span() == 0)
						{
							Shopper->set_state("2");
						}
					}

					if (temp_object->x() > 4000)
					{
						mainCharacter->setIsDying(true);
						gameCase = GAMECASES::COMPLETE;
						if (_soundTheme->IsSoundPlaying())
							_soundTheme->Stop();
						_soundComplete->Play();
						MyCamera::GetInstance()->setPosition((MyCamera::GetInstance()->View().right - MyCamera::GetInstance()->View().left) / 2 + 200, MyCamera::GetInstance()->y());
						mainCharacter->setPosition((MyCamera::GetInstance()->View().right - MyCamera::GetInstance()->View().left) + 200, MyCamera::GetInstance()->y() + 50);
						mainCharacter->setState("700");
						Abu->set_state("2");
					}


					break;

				 
				case 8://Stairs
				{

					//2226 - 2680 == BOUNDARY_STAIRS
					if (temp_object->x() > 2226 && temp_object->x() < 2680
						&&
						(mainCharacter->ChosenLayer() == 0
							|| (temp_object->y() < BOUNDARY_STAIRS && mainCharacter->ChosenLayer() != 2)))
					{
						break;
					}

					if (temp_object->x() > 2226 && temp_object->x() < 2680)
					{
						//find TriggerLeft and TriggerRight



						if (mainCharacter->ChosenLayer() > 0)
						{
							if (temp_object->y() > BOUNDARY_STAIRS)
							{
								if (TriggerRight->animaDelay() > 0)
								{
									TriggerRight->setAnimaDelay(0);

									if (TriggerRight->curface() == GameObject::RIGHT)
									{
										TriggerRight->set_curFace(GameObject::LEFT);
										mainCharacter->set_ChosenLayer(0);
									}
									else
									{
										TriggerRight->set_curFace(GameObject::RIGHT);
										mainCharacter->set_ChosenLayer(1);
									}
								}



								if (mainCharacter->ChosenLayer() <= 0)
								{
									break;
								}

							}
							else
							{

								if (mainCharacter->ChosenLayer() != 2)
								{
									break;
								}
							}

							if (mainCharacter->vx() > 0 && (mainCharacter->ChosenLayer() == 1 || mainCharacter->ChosenLayer() == 2)
								&& mainCharacter->x() > 2333
								)
							{
								TriggerLeft->setVisible(true);
							}
						}
					}

					//Default Collision
					if (collisionResult._collisionSide == DOWNBOTTOM)
					{
						mainCharacter->set_vy(-collisionResult._collisionIndex*mainCharacter->vy());
					}
					if (collisionResult._collisionSide == UPTOP)
					{
						mainCharacter->set_vy((collisionResult._collisionIndex*mainCharacter->vy()));
					}
					if (collisionResult._collisionSide == LEFT || collisionResult._collisionSide == RIGHT)
					{
						/*	if (temp_object->y() == 590)
						{
						mainCharacter->set_ChosenLayer(2);
						}*/
						mainCharacter->set_vy(-temp_object->height()/4);

					}
					mainCharacter->set_IsWalkingStairs(true);

				}
				break;
				case 41://Diamond
					if (temp_object->IsDisappearing() == false)
					{
						_itemsList->push_back(temp_object);

						mainCharacter->setScore(mainCharacter->Score() + 150);
						mainCharacter->setDiamondCount(mainCharacter->DiamondCount() + 1);
						temp_object->set_state("1");
						temp_object->setDisappearing(true);
						PlaySound(_soundGem);
					}
					break;
				case 42://Heart

					if (temp_object->IsDisappearing() == false)
					{
						_itemsList->push_back(temp_object);

						mainCharacter->setScore(mainCharacter->Score() + 150);
						
						mainCharacter->set_health(mainCharacter->health() + 1);
						temp_object->set_state("1");
						temp_object->setDisappearing(true);
					}

					break;
				case 44://CheckpointJar
					if (temp_object->IsRepeating() == true)
					{
						mainCharacter->setPositionCheckpoint(temp_object->Position());
						temp_object->set_state("1");
						temp_object->setIsRepeating(false);
					}
					break;
				case 43://AbuFace 
					if (temp_object->IsDisappearing() == false)
					{
						_itemsList->push_back(temp_object);

						mainCharacter->setScore(mainCharacter->Score() + 250);
						temp_object->set_state("1");
						temp_object->setDisappearing(true);
					}
					break;
				case 45://GenieFace

					if (temp_object->IsDisappearing() == false)
					{
						_itemsList->push_back(temp_object);

						mainCharacter->setScore(mainCharacter->Score() + 250);
						temp_object->set_state("1");
						temp_object->setDisappearing(true);
						if (_soundWow->IsSoundPlaying() == false)
							PlaySound(_soundWow);
					}
					break;
				case 46://GenieLamp
					temp_object->setVisible(false);
					for (auto temp = _healthHavingList->begin(); temp != _healthHavingList->end(); temp++)
						
					{
						temp_object_move = *temp;
						if (find(_onScreenList->begin(), _onScreenList->end(), (GameObject*)temp_object_move) != _onScreenList->end())
						{

							temp_object_move->set_health(0);
						}

					}
						

					break;




				case 5://FloatGround

					if (collisionResult._collisionSide == Side::UPTOP || collisionResult._collisionSide == Side::NONE)
					{
						{
							/*if (collisionResult._collisionIndex == 0.0f)*/
							{
								mainCharacter->set_vy(0);
								mainCharacter->set_main_state("0");
								//temp_object->set_vy(GRAVITY * 2);
								temp_object->set_is_hitted(true);
								temp_object->setIsRepeating(false);
							}
							/*	else
							mainCharacter->set_vy((collisionResult._collisionIndex*mainCharacter->vy()));*/

						}

					}

					break;
				case 6://SpringBoard
					   /*if (collisionResult._collisionSide==UPTOP)
					   {*/
					if (collisionResult._collisionIndex == 0.0f)
					{
						mainCharacter->set_sub_state("6");
						mainCharacter->set_vy(JUMP_FORCE*1.2);
						mainCharacter->set_jump_step_remaining(JUMP_STEP);
						temp_object->set_is_hitted(true);
					}
					else
					{
						mainCharacter->set_vy(mainCharacter->vy()*collisionResult._collisionIndex);
					}

					_soundSpringBoard->Play();
					break;
				case 7://Camel
					if (mainCharacter->sub_state() == "1" && collisionResult._collisionSide == UPTOP)
					{
						//trace(L"%d", temp_object->state_manager()->life_span());

						if (collisionResult._collisionIndex == 0.0f)
						{
							mainCharacter->set_sub_state("2");
							//mainCharacter->setPosition(mainCharacter->x() + collisionResult._collisionIndex*mainCharacter->vx()*FIXED_TIME, mainCharacter->y() + collisionResult._collisionIndex*mainCharacter->vy()*FIXED_TIME);

							mainCharacter->set_vy(JUMP_FORCE*0.5);
							//event 
							_camel->set_state("001");
							//spawn a camel saliva
							D3DXVECTOR3 temp_pos = _camel->CalPositon(MID_RIGHT);
							camel_saliva->setPosition(temp_pos.x, temp_pos.y);
							_camel->set_weapon_obj(camel_saliva);
							camel_saliva->set_vx(5);
							_camel->set_is_throwing(true);
							camel_saliva->setVisible(true);
							//_disposableList->push_back(camel_saliva);
							_gameObjectList->push_back(camel_saliva);
							_onScreenList->push_back(camel_saliva);
							//sound
							_soundCamel->Play();

						}
						else
						{
							mainCharacter->set_vy(mainCharacter->vy()*collisionResult._collisionIndex);
						}
					}
					break;
				case 11:case 12:
				case 13:case 14: case 15:
					mainCharacter->BeBeaten();
					break;

				default: {}
				}
			}
		}
	}
	for (list<GameObject*>::iterator obj = _onScreenList->begin(); obj != _onScreenList->end(); obj++)
	{
		//Process sword 
		temp_object = *obj;
		int collisionNameID = mapIdName[temp_object->get_name()];
		if (temp_object->get_name() == "Rope" || temp_object->get_name()=="HorizontalBar" || temp_object->Visbile() == false || temp_object->get_name()=="Camel"|| collisionNameID>40 || collisionNameID==0)
			
			continue;
		for (auto ab = mainCharacter->bullet_list()->begin(); ab != mainCharacter->bullet_list()->end(); ab++)
		{

			temp_bullet = *ab;
			
			if (temp_bullet->Visbile() == true)
			{
				
				CollisionResult collisionIndex = CheckCollision(*ab, *obj);
				if (collisionIndex._collisionIndex<1.0f && collisionIndex._collisionIndex > 0.0f)
				{

					temp_bullet->set_vx(collisionIndex._collisionIndex * temp_bullet->vx());
					temp_bullet->set_vy(collisionIndex._collisionIndex * temp_bullet->vy());
					break;
				}
				if (collisionIndex._collisionIndex == 0.0f)
				{
					temp_bullet->set_is_popping(true);
					temp_bullet->state_manager()->setState("001");
					temp_bullet->set_vx(0);
					temp_bullet->set_vy(0);
					temp_object_move = (GameObjectMove*)*obj;
					_soundAppleCollision->Play();
					switch (mapIdName[temp_object_move->get_name()])
					{
					case 13:
						if (temp_object_move->is_immune() == 0.0f)
						{
							PlaySound(_soundPantDrop);
						}
						
					case 20: case 11: case 12: case 14: 
						
						if (temp_object_move->is_immune() == 0.0f)
						{
							PlaySound(_soundHitted);
							temp_object_move->set_health(temp_object_move->health() - 1);
							temp_object_move->set_is_immune(20);
							temp_object_move->set_state("003");
							temp_object_move->set_hand_state("3");
							temp_object_move->state_manager()->set_life_span(temp_object_move->state_manager()->getStateByCode("003").getListRect().size());
							temp_object_move->setIsRepeating(false);
						}
						break;

					}
				}

			}
			temp_bullet = *ab;

		}

		if (SimpleIntersect(mainCharacter->sword(), &temp_object->bounding_box()))
		{
			temp_object_move = (GameObjectMove*)*obj;
			switch (mapIdName[temp_object_move->get_name()])
			{
			case 20:
				{
					if (temp_object_move->hand_state()=="1")
						if (temp_object_move->is_immune() == 0.0f)
						{
							temp_object_move->set_health(temp_object_move->health() - 1);

						}
					break;
				}
			case 13:
				if (temp_object_move->is_immune() == 0.0f)
				{
					PlaySound(_soundPantDrop);
				}
			case 11: case 12: case 14: case 15:
			{
				if (temp_object_move->is_immune() == 0.0f)
				{
					PlaySound(_soundHitted);
					temp_object_move->set_health(temp_object_move->health() - 1);
					temp_object_move->set_is_immune(20);
					temp_object_move->set_state("003");
					temp_object_move->set_hand_state("3");
					temp_object_move->state_manager()->set_life_span(temp_object_move->state_manager()->getStateByCode("003").getListRect().size());
					temp_object_move->setIsRepeating(false);
				}
				break;
			}
			}
		}
	}
	quadtree->Clear();
	delete quadtree;
}
void Scene1::PhysicsUpdate(float t)
{
	//handle for camel
	if (std::find(_onScreenList->begin(), _onScreenList->end(), _camel) != _onScreenList->end())
	{
		if (_camel->state_manager()->life_span() == 0)
			_camel->set_state("000");
	}

	EnemyHandle(t);
	DisposablePhysicUpdate(t);

	//critical bug

	if (mainCharacter->vy() == 0 && mainCharacter->sub_state() !="2")
	{
		if (mainCharacter->isSwinging() == false)
			mainCharacter->set_sub_state("0");
	}
	if (mainCharacter->vy() > 0)
	{
		mainCharacter->set_sub_state("1");
	}

	if (mainCharacter->isClimbing() == false && mainCharacter->isSwinging() == false) {
		mainCharacter->set_vy(mainCharacter->vy() + GRAVITY);
		if (mainCharacter->vy() > 7)
			mainCharacter->set_vy(7);
	}
	else
		if (mainCharacter->vy() == 0)
		{
			MyCamera::GetInstance()->set_vy(0);
		}

	if (mainCharacter->IsDying() == false)
		CollisionDetect();
	else
	{
		mainCharacter->set_vy(0);
		mainCharacter->set_vx(0);
	}

	if (mainCharacter->on_state_end() == false)
	{
		mainCharacter->setState(mainCharacter->main_state() + mainCharacter->sub_state() + mainCharacter->hand_state());
	}
	
	mainCharacter->PhysicUpdate(t);

}
void Scene1::GraphicUpdate(float t)
{

	if (temp_burnfx->Visbile() == false)
		_gameObjectList->remove(temp_burnfx);
	
	mainCharacter->GraphicUpdate(t);
	MyCamera::GetInstance()->Update(t);


	if (mainCharacter->IsDying() == true && (gameCase == GAMECASES::CHOSING || gameCase == GAMECASES::CONTINUE || gameCase == GAMECASES::QUIT))
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3ddev->StretchRect(wishBackground, NULL, backbuffer, NULL, D3DTEXF_NONE);
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
		sprite_handler->SetTransform(&old_matrix);
		Abu->GraphicUpdate(t);

		if (gameCase == GAMECASES::QUIT)
		{

			if (MyCamera::GetInstance()->View().left >= Abu->bounding_box().right)
			{ 
				SceneHome* sceneHome = new SceneHome();
				GameManager::GetInstance()->ReplaceScene(sceneHome);
			}

			mainCharacter->set_vx(-CHARACTER_VX);
			mainCharacter->setPosition(mainCharacter->x() - 3, mainCharacter->y());
		}
		if (gameCase == GAMECASES::CONTINUE)
		{
			if (MyCamera::GetInstance()->View().right <= mainCharacter->bounding_box().left)
			{
				gameCase = GAMECASES::PLAYING;

				mainCharacter->WishContinue();

				Abu->set_state("0");
				return;
			}

			mainCharacter->set_vx(CHARACTER_VX);
			mainCharacter->setPosition(mainCharacter->x() + 3, mainCharacter->y());
		}

		mainCharacter->setTranslation(D3DXVECTOR2(mainCharacter->x() - MyCamera::GetInstance()->View().left, mainCharacter->y() - MyCamera::GetInstance()->View().top));
		mainCharacter->Render(false, true, true);
		Abu->setPosition(mainCharacter->x() + 50, mainCharacter->y());
		Abu->setTranslation(D3DXVECTOR2(Abu->x() - MyCamera::GetInstance()->View().left, Abu->y() - MyCamera::GetInstance()->View().top));
		 
		Abu->Render();
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
		return;
	}

	if (mainCharacter->IsDying() == true && gameCase == GAMECASES::COMPLETE)
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3ddev->StretchRect(completeBackground, NULL, backbuffer, NULL, D3DTEXF_NONE);
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
		sprite_handler->SetTransform(&old_matrix);
		Abu->GraphicUpdate(t);


		if (MyCamera::GetInstance()->View().left >= mainCharacter->bounding_box().right)
		{
			//PostMessage(hwnd, WM_DESTROY, 0, 0);
			//this->Game_End(hwnd);
			Scene2* scene2 = new Scene2();
			GameManager::GetInstance()->ReplaceScene(scene2);
			 
		}
		mainCharacter->setPosition(mainCharacter->x() - 3, mainCharacter->y());



		mainCharacter->setTranslation(D3DXVECTOR2(mainCharacter->x() - MyCamera::GetInstance()->View().left, mainCharacter->y() - MyCamera::GetInstance()->View().top));
		mainCharacter->Render(false, true, true);
		Abu->setPosition(mainCharacter->x() - 50, mainCharacter->y());
		Abu->setTranslation(D3DXVECTOR2(Abu->x() - MyCamera::GetInstance()->View().left, Abu->y() - MyCamera::GetInstance()->View().top));
		Abu->Render();
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
		return;
	}


	if (mainCharacter->IsDying() == true && gameCase == GAMECASES::PLAYING)
	{

		if (_soundTheme->IsSoundPlaying())
		{
			_soundTheme->Stop();
		}
		
		for (auto i = _healthHavingList->begin(); i != _healthHavingList->end(); i++)
		{
			temp_object_move = *i;
			temp_object_move->setVisible(true);
			temp_object_move->set_state("000");
			temp_object_move->set_hand_state("0");
			temp_object_move->setIsRepeating(true);
			if (temp_object_move->get_name() != "EnemyHand")
				temp_object_move->set_health(2);
			else temp_object_move->set_health(1);
		}
		for (auto i = _itemsList->begin(); i != _itemsList->end(); i++)
		{
			temp_object = *i;
			temp_object->Reset();
			temp_object->setVisible(true);
			temp_object->setDisappearing(false);
			if (temp_object->get_name() == "Apple")
				temp_object->state_manager()->setState("000");
			else
				temp_object->state_manager()->setState("0");
		}


		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3ddev->StretchRect(NULL, NULL, backbuffer, NULL, D3DTEXF_NONE);

		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
		sprite_handler->SetTransform(&old_matrix);
		Abu->GraphicUpdate(t);

		mainCharacter->setTranslation(D3DXVECTOR2(mainCharacter->x() - MyCamera::GetInstance()->View().left, mainCharacter->y() - MyCamera::GetInstance()->View().top));
		mainCharacter->Render(false, true, true);


		Abu->setPosition(mainCharacter->x() + 50, mainCharacter->y());
		Abu->setTranslation(D3DXVECTOR2(Abu->x() - MyCamera::GetInstance()->View().left, Abu->y() - MyCamera::GetInstance()->View().top));
		Abu->Render();

		if (mainCharacter->state_manager()->life_span() == 1 && mainCharacter->Life() == 0 && gameCase == GAMECASES::PLAYING)
		{
			Abu->state_manager()->setState("1");
			gameCase = GAMECASES::CHOSING;
			mainCharacter->setState("000");
		}
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
		return;
	}

	 

	//Render Everything
	try
	{
		if (_soundTheme->IsSoundPlaying() == false)
			_soundTheme->Play(0, DSBPLAY_LOOPING);
		 
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		viewRect = MyCamera::GetInstance()->View();
		d3ddev->BeginScene();
		//erase the entire background 

		//start sprite handler 	
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

		background->Render();
		//trace(L"%d", _explosion->state_manager()->life_span());
		if ((_explosion->state_manager()->life_span() == 0) /*|| (find(_onScreenList->begin(), _onScreenList->end(), _explosion) == _onScreenList->end())*/)
		{
			_explosion->state_manager()->setState("001");
			_explosion->setVisible(false);
			//_explosion->Reset();
			/*if (find(_onScreenList->begin(), _onScreenList->end(), _explosion) != _onScreenList->end())
				_onScreenList->remove(_explosion);
			_gameObjectList->remove(_explosion);*/
		}
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->Draw(mapETC, &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

		mainCharacter->setTranslation(D3DXVECTOR2(mainCharacter->x() - MyCamera::GetInstance()->View().left, mainCharacter->y() - MyCamera::GetInstance()->View().top));
		mainCharacter->DrawBullet();
		//mainCharacter->RenderBounding(D3DCOLOR_ARGB(200, 255, 67, 78));


		for (auto i = _onScreenList->begin(); i != _onScreenList->end(); i++)
		{
			temp_object = *i;
			//temp_object->setAnchor(AnchorPoint::BOTTOM_MID);
			temp_object->setTranslation(D3DXVECTOR2(temp_object->x() - viewRect.left, temp_object->y() - viewRect.top));
			if (temp_object->sprite()->image())
			{
				if (temp_object->get_name() == "Explosion" && temp_object->Visbile() == true)
					int a = 5;
				temp_object->Render(false, true, true);
				temp_object->GraphicUpdate(t);
			}
		//	temp_object->RenderBounding(D3DCOLOR_ARGB(200, 255, 67, 78));
		}
		mainCharacter->Render(false, true, true);




#pragma region Draw map_front
		viewRect.top += mapinfo->Height / 2;
		viewRect.bottom += mapinfo->Height / 2;
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->Draw(mapETC, &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));




#pragma endregion


		ShopperText->GraphicUpdate(t);
		if (ShopperText->curface() == GameObject::LEFT)
		{
			ShopperText->setPosition(ShopperText->x() - CHARACTER_VX - 10, ShopperText->y());
			if (ShopperText->bounding_box().right <= MyCamera::GetInstance()->View().left)
			{
				ShopperText->setVisible(false);
				ShopperText->set_curFace(GameObject::RIGHT);
			}
		}
		ShopperText->setTranslation(D3DXVECTOR2(ShopperText->x() - MyCamera::GetInstance()->View().left, ShopperText->y() - MyCamera::GetInstance()->View().top));
		ShopperText->Render(false, true, true);



		//mainCharacter->RenderBounding(D3DCOLOR_ARGB(150, 0, 250, 0));
		_UI->Render(mainCharacter->health(), mainCharacter->Life(), mainCharacter->appleCount(), mainCharacter->DiamondCount(), mainCharacter->Score());
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
	}
	catch (int e)
	{
		return;
	}



}


void Scene1::LoadListObjectXml(char* xmlpath)
{
	xml_document fileXml;
	xml_parse_result result = fileXml.load_file(xmlpath);
	xml_node root = fileXml.child("map");

	map<string, char* > mapSpritePath;
	//map<string, char*> mapStatePath;

	for (xml_node node : root.children("tileset"))
	{
		//add mapSprite elements
		string name = node.attribute("name").value();

		string pathSprite = node.child("image").attribute("source").value();
		char* cPathSprite = new char[pathSprite.length() + 1];
		memcpy(cPathSprite, pathSprite.c_str(), pathSprite.length() + 1);
		mapSpritePath[name] = cPathSprite;

		//add mapState elements
		string pathState = node.child("statexml").attribute("source").value();

	}


	for (xml_node node : root.children("objectgroup"))
	{
		map<int, string> mapName;


		string name = node.attribute("name").value();
		char* objectName = new char[name.length() + 1];
		memcpy(objectName, name.c_str(), name.length() + 1);

		int idName = atoi(node.attribute("id").value());



		//check if pathSprite constained  in map
		string pathSprite = "";
		if (mapSpritePath.count(name) != 0)
			pathSprite = mapSpritePath[name];
		char* cPathSprite = new char[pathSprite.length() + 1];
		memcpy(cPathSprite, pathSprite.c_str(), pathSprite.length() + 1);


		float anchorTransformX = 0;
		float anchorTransformY = 0;
		//string face = node.attribute("face").value();
		for (xml_node object = node.first_child(); object; object = object.next_sibling())
		{
			anchorTransformX = atoi(object.attribute("width").value()) / 2;
			if (name == "Ground" || name == "HorizontalBar" || name == "Rope" || name == "Wall"
				|| name == "Stairs" || name == "FireGround" || name == "Trigger"
				)
			{
				anchorTransformY = atoi(object.attribute("height").value());
			}

			if (name == "Diamond" || name == "Heart" || name == "AbuFace" || name == "CheckpointJar" || name == "GenieFace" || name == "GenieLamp")
			{
				anchorTransformY = atoi(object.attribute("height").value()) / 2;
				anchorTransformX = atoi(object.attribute("width").value()) / 2;
			}
			if (name == "SpringBoard")
			{
				anchorTransformX = 0;
				anchorTransformY = -atoi(object.attribute("height").value()) / 2;
			}

			GameObject * anObject;
			switch (idName)
			{
			case 0:
				anObject = new GameObject();
				ApplePrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 1:
				anObject = new GameObject();
				GroundPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 2:
				anObject = new GameObject();
				WallPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 3:
				anObject = new GameObject();
				RopePrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 4:
				anObject = new GameObject();
				HorizontalBarPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 5:
				anObject = new GameObject();
				FloatGroundPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				floatGroundList->push_back(anObject);
				initFloatGroundList.insert(initFloatGroundList.end(), anObject->Position());
				break;
			case 6:
				anObject = new GameObject();
				SpringBoardPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 7:
				anObject = new GameObjectMove();
				CamelPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				_camel = (GameObjectMove*)anObject;
				break;
			case 8:
				anObject = new GameObject();
				StairsPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 9:
				anObject = new GameObject();
				FireGroundPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				listFireGround->push_back(anObject);
				break;
			case 10:
				anObject = new GameObjectMove();
				EnemyHandPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value())
					, atoi(object.attribute("xmin").value()), atoi(object.attribute("xmax").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
				break;
			case 11:
				anObject = new GameObjectMove();
				EnemyThinPrefab::Instantiate((GameObjectMove *)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value())
					, atoi(object.attribute("xmin").value()), atoi(object.attribute("xmax").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
				break;
			case 12:
				anObject = new GameObjectMove();
				EnemyMusPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value())
					, atoi(object.attribute("xmin").value()), atoi(object.attribute("xmax").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
				break;
			case 13:
				anObject = new GameObjectMove();

				EnemyFatPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value())
					, atoi(object.attribute("xmin").value()), atoi(object.attribute("xmax").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
				if (assigned == false)
				{
					assigned = true;
					camel_target = (GameObjectMove*)anObject;
				}
				break;
			case 14:
				anObject = new GameObjectMove();
				EnemyJugPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value())
					, atoi(object.attribute("xmin").value()), atoi(object.attribute("xmax").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
				break;
			case 15:
				anObject = new GameObjectMove();
				EnemyJarPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value())
					, atoi(object.attribute("xmin").value()), atoi(object.attribute("xmax").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
				break;
			case 30:
				anObject = new GameObject();
				ShopperPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 31:
				anObject = new GameObject();
				TriggerPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 33:
				anObject = new GameObject();
				ShopperTextPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				ShopperText = anObject;
				continue;
			case 41:
				anObject = new GameObject();
				DiamondPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;

			case 42:
				anObject = new GameObject();
				HeartPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;

			case 43:
				anObject = new GameObject();
				AbuFacePrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;

			case 44:
				anObject = new GameObject();
				CheckpointJarPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;

			case 45:
				anObject = new GameObject();
				GenieFacePrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;

			case 46:
				anObject = new GameObject();
				GenieLampPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			
			case 47: 
				anObject = new GameObject();

				CeilingPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			default:
				anObject = new GameObject();
				break;

			}
			anObject->setAnchor(AnchorPoint::BOTTOM_MID);
			/*if (idName == 30)
			anObject->setAnchor(AnchorPoint::TOP_LEFT);*/
			if (idName == 41 || idName == 42 || idName == 43 || idName == 44 || idName == 45 || idName == 46)
				anObject->setAnchor(AnchorPoint::MIDDLE);
			if (idName == 6)
			{
				anObject->setAnchor(AnchorPoint::MID_LEFT);
				listSpringBoard->push_back(anObject);
			}

			anObject->set_bounding_box(CalculateBoundingBox(anObject->x(), anObject->y(), anObject->width(), anObject->height(), anObject->anchor()));
			(CalculateBoundingBox(anObject->x(), anObject->y(), anObject->width(), anObject->height(), anObject->anchor()));

			_gameObjectList->push_back(anObject);
		}
	}
}



//the main game loop content
void Scene1::Game_Run(HWND hwnd, int dt)
{
	GameTime::GetInstance()->StartCounter();
	InputUpdate();

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	DWORD now = GetTickCount();
	//this keeps the game running at a steady frame rate
	float t = now - start;
	if (t >= 1000 / FPS)
	{

		//reset timing
		start = now;
		if (t < FIXED_TIME)
			Sleep(FIXED_TIME - t);
		_onScreenList = OnScreenDetect();
		if (mainCharacter->IsDying() == false || (mainCharacter->IsDying() == true && mainCharacter->Life() == 0))
		{
			PhysicsUpdate(FIXED_TIME);
		}
		GraphicUpdate(FIXED_TIME);
		_onScreenList->clear();
	}
	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
	//check for escape key (to exit program)	
	//if (KEY_PRESSED(VK_ESCAPE))
	//{
	//	dikeyboard->Unacquire();
	//	SceneHome* sceneHome = new SceneHome();
	//	GameManager::GetInstance()->ReplaceScene(sceneHome);
	//}

}

void Scene1::Game_End(HWND hwnd)
{
	Game::Game_End(hwnd);
}


Scene1::~Scene1()
{
}
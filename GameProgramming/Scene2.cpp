#include "Scene2.h"
#include "JafarPrefab.h"
#include "GameTime.h"
#include "dxinput.h"
#include "StarBulletPrefab.h"
#include "trace.h"
#include "FireBulletPrefab.h"
#include "ApplePrefab.h"
#include "GroundPrefab.h"
#include "WallPrefab.h"
#include "FireGroundPrefab.h"
#include "StarBullet.h"
#include "BurningEffectPrefab.h"
#include "SceneHome.h"


#define FLOOR_Y 438
#define JUMPFORCE_SCENE2 -21
#define GRAVITY_SCENE2 1
#define JUMP_STEP_SCENE2 9
//for allocating purpose
bool bulletCollideScene2;
int fireRemainToVisiblizeApple;
StarBullet* temp_star;
StarBullet* temp_star_handle;
GameObject* temp_object_scene2;
int _markOdd;
GameObject* temp_bullet_scene2;
GameObject* temp_burnfx_scene2;
AppleBullet* temp_apple_bullet_scene2;
GameObject* magicExplosion;
list<GameObject*>* _appleList;
bool drawOneOnAnime;
//timing variable
DWORD startScene2 = GetTickCount();
int Scene2::Game_Init(HWND hwnd)
{
	////initialize keyboard 
	//if (!Init_Keyboard(hwnd))
	//{
	//	MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
	//	return 0;
	//}
	//init background and camera procedure
	Game::Game_Init(hwnd);
	mapinfo = new D3DXIMAGE_INFO();
	temp_burnfx_scene2 = new GameObject();
	BurningEffectPrefab::Instantiate(temp_burnfx_scene2);
	fireRemainToVisiblizeApple = 8;
	_soundAnaconda = LoadSound("Res/Audio/JafarSnake.wav");
	animateBackground.top = 0;
	animateBackground.bottom = 880;
	animateBackground.left = 0;
	animateBackground.right = 2200 * 3 / 5;


	mapETC = LoadTexture("Res/SceneBoss/JafarPalaceFinalBackground.png", D3DCOLOR_XRGB(63, 72, 204), mapinfo);
	background = LoadSurface("Res/SceneBoss/backgroundJafar.png", D3DCOLOR_XRGB(63, 72, 204));
	MyCamera::GetInstance()->setCurMapWidth(mapinfo->Width);
	MyCamera::GetInstance()->setCurMapHeight(mapinfo->Height * 2);
	//init components game objects
	drawOneOnAnime = false;
	_appleList = new list<GameObject*>();
	magicExplosion = new GameObject();
	temp_star_handle = new StarBullet();
	_gameObjectList = new list<GameObject*>();
	_onScreenList = new list<GameObject*>();
	_disposableList = new list<GameObject*>();
	_enemyBulletStarList = new list<StarBullet*>();
	_enemyBulletFireList = new list<GameObject*>();
	LoadListObjectXml("Res/Scene2XML.xml");
	mapIdName["Apple"] = 0;
	mapIdName["Ground"] = 1;
	mapIdName["Wall"] = 2;
	mapIdName["FireGround"] = 3;
	mapIdName["StarBullet"] = 99;
	mapIdName["FireLand"] = 100;
	mapIdName["Jafar"] = 101;
	//magicExplosionPrefab
	_Jafar = new GameObjectMove();
	JafarPrefab::Instantiate(_Jafar, 640, 400);
	magicExplosion = new GameObject();
	magicExplosion->setSprite(new Sprite("Res\\explosion.png", 0, 0));
	magicExplosion->set_state_manager(new StateManager("Res\\MagicExplosionXML.xml"));
	magicExplosion->state_manager()->AddToDictState("001", "Exploding");
	magicExplosion->state_manager()->AddToDictState("000", "Empty");
	magicExplosion->setPosition(0, 0);
	magicExplosion->setVisible(false);
	magicExplosion->setIsRepeating(false);
	magicExplosion->set_state("000");
	_gameObjectList->push_back(magicExplosion);
	_gameObjectList->push_back(temp_burnfx_scene2);
	_gameObjectList->push_back(_Jafar);
	_mainCharacter = new Aladdin();
	_mainCharacter->setAnchor(AnchorPoint::BOTTOM_MID);
	_mainCharacter->set_state("000");
	_mainCharacter->setPosition(980, 380);
	_mainCharacter->setPositionCheckpoint(_mainCharacter->Position());
	MyCamera::GetInstance()->setPosition(980, 380);
	//MyCamera::GetInstance()->setPosition(100, 521);
	//Init components 
	_UI = new UIScene();
#pragma region Sound
	_soundTheme = LoadSound("Res/Audio/BossTune.wav");
	_soundJump = LoadSound("Cuica-1.wave");
	_soundSlash = LoadSound("Res/Audio/IdleDownSplash.wave");
	_soundCollectApple = LoadSound("Res/Audio/AppleCollect.wave");
	_soundAppleCollision = LoadSound("Res/Audio/AppleThrowCollision.wave");


	_soundWin = LoadSound("Res/Audio/AWholeNewWorld.wav");

	if (_soundTheme == NULL)
		return 0;
	_soundTheme->Play(0, DSBPLAY_LOOPING);

#pragma endregion
	return 1;
}



void Scene2::CollisionDetect()
{
	Quadtree* quadtree = Quadtree::CreateQuadtree(MyCamera::GetInstance()->bounding_box().left, MyCamera::GetInstance()->bounding_box().top, MyCamera::GetInstance()->bounding_box().right, MyCamera::GetInstance()->bounding_box().bottom);

	std::list<GameObject*>* return_object_list = new std::list<GameObject*>();
	quadtree->Retrieve(return_object_list, MyCamera::GetInstance());
	for (auto x = return_object_list->begin(); x != return_object_list->end(); x++)
	{
		temp_object_scene2 = *x;
		if (temp_object_scene2->Visbile() == true)
		{
			_mainCharacter->set_bounding_box(CalculateBoundingBox(_mainCharacter->x(), _mainCharacter->y(), _mainCharacter->width(), _mainCharacter->height(), _mainCharacter->anchor()));
			temp_object_scene2->set_bounding_box(CalculateBoundingBox(temp_object_scene2->x(), temp_object_scene2->y(), temp_object_scene2->width(), temp_object_scene2->height(), temp_object_scene2->anchor()));


			CollisionResult collisionResult = CheckCollision(_mainCharacter, temp_object_scene2);


			if (collisionResult._collisionIndex < 1 && collisionResult._collisionIndex >= 0)
			{
				//_mainCharacter collision with others z
				int collisionNameID = mapIdName[temp_object_scene2->get_name()];
				switch (collisionNameID)
				{

				case 0://Apple
					if (temp_object_scene2->IsDisappearing() == false)
					{
						_mainCharacter->setAppleCount(_mainCharacter->appleCount() + 1);
						temp_object_scene2->set_state("1");
						temp_object_scene2->setDisappearing(true);
					}
					//sound
					//_soundCollectApple->Play();
					break;
				case 3://FireGround

					if (collisionResult._collisionSide == UPTOP)
					{
						_mainCharacter->set_vy((collisionResult._collisionIndex*_mainCharacter->vy()));
					}
					if (collisionResult._collisionIndex == 0.0f)
					{
						if (collisionResult._collisionSide == UPTOP)
						{
							if (_mainCharacter->sub_state() == "1" && _mainCharacter->state_manager()->life_span() == 3)
							{
								_mainCharacter->set_on_state_end(true);
								_mainCharacter->set_state("0002");
								_mainCharacter->set_degree_state("2");
							}
							if (_Jafar->main_state() == "1")
							{
								if (_mainCharacter->vx() < 0)
									temp_burnfx_scene2->setPosition(_mainCharacter->x() + 30, _mainCharacter->y());
								else
									if (_mainCharacter->vx() > 0)
										temp_burnfx_scene2->setPosition(_mainCharacter->x() - 30, _mainCharacter->y());
									else
									{
										temp_burnfx_scene2->setPosition(_mainCharacter->x(), _mainCharacter->y());

									}
								temp_burnfx_scene2->set_state("001");
								temp_burnfx_scene2->setVisible(true);
								temp_burnfx_scene2->setIsRepeating(true);
								if (_mainCharacter->vx() == 0 || _mainCharacter->last_face() != _mainCharacter->curface())
									_mainCharacter->BeBeaten();
							}




						}
					}
					break;
				case 1://Ground

					if (collisionResult._collisionSide == DOWNBOTTOM)
					{
						_mainCharacter->set_vy(-collisionResult._collisionIndex*_mainCharacter->vy());
					}
					if (collisionResult._collisionSide == UPTOP)
					{
						_mainCharacter->set_vy((collisionResult._collisionIndex*_mainCharacter->vy()));
					}
					if (collisionResult._collisionIndex == 0.0f)
					{
						if (collisionResult._collisionSide == UPTOP)
						{
							if (_mainCharacter->sub_state() == "1" && _mainCharacter->state_manager()->life_span() == 3)
							{
								_mainCharacter->set_on_state_end(true);
								_mainCharacter->set_state("0002");
								_mainCharacter->set_degree_state("2");
							}
						}
						if ((_mainCharacter->curface() == GameObject::RIGHT) && collisionResult._collisionSide == Side::LEFT && _mainCharacter->vx() > 0)
						{
							_mainCharacter->set_vx(0);
						}
						if ((_mainCharacter->curface() == GameObject::LEFT) && collisionResult._collisionSide == Side::RIGHT && _mainCharacter->vx() < 0)
						{
							_mainCharacter->set_vx(0);
						}
						temp_burnfx_scene2->setVisible(false);
					}
					break;
				case 2: //Wall 

					if (collisionResult._collisionSide == NONE)//|| collisionResult._collisionSide == LEFT || collisionResult._collisionSide == RIGHT)
					{
						float newXPosition = _mainCharacter->x();
						if (_mainCharacter->curface() == GameObject::RIGHT)
						{
							_mainCharacter->set_FacePush(GameObject::RIGHT);
							if (_mainCharacter->CurrentState() == "Push")
							{
								int nextWidth = _mainCharacter->state_manager()->curState().MaxBounding().right - _mainCharacter->state_manager()->curState().MaxBounding().left;
								newXPosition = temp_object_scene2->bounding_box().left - nextWidth / 2 - CHARACTER_VX*FIXED_TIME;
							}
							else
							{
								//newXPosition = temp_object_scene2->bounding_box().left - 21;
								int nextWidth = _mainCharacter->state_manager()->curState().MaxBounding().right - _mainCharacter->state_manager()->curState().MaxBounding().left;
								newXPosition = temp_object_scene2->bounding_box().left - nextWidth / 2 - CHARACTER_VX*FIXED_TIME;
							}
						}
						else
						{
							_mainCharacter->set_FacePush(GameObject::LEFT);
							if (_mainCharacter->CurrentState() == "Push")
							{
								int nextWidth = _mainCharacter->state_manager()->curState().MaxBounding().right - _mainCharacter->state_manager()->curState().MaxBounding().left;
								newXPosition = temp_object_scene2->bounding_box().right + nextWidth / 2 + CHARACTER_VX*FIXED_TIME;
							}
							else
							{
								//	newXPosition = temp_object_scene2->bounding_box().right + 21;
								int nextWidth = _mainCharacter->state_manager()->curState().MaxBounding().right - _mainCharacter->state_manager()->curState().MaxBounding().left;
								newXPosition = temp_object_scene2->bounding_box().right + nextWidth / 2 + CHARACTER_VX*FIXED_TIME;
							}
						}
						_mainCharacter->setPosition(newXPosition, _mainCharacter->y());
						//MyCamera::GetInstance()->setPosition(newXPosition, _mainCharacter->y());
						break;
					}
					_mainCharacter->set_vx(0);
					_mainCharacter->set_sub_state("3");
					//if (_mainCharacter->vx() != 0 && _mainCharacter->sub_state() != "1" && _mainCharacter->sub_state() != "2")
					break;

				case 101:
				{
					if (SimpleIntersect(&_Jafar->bounding_box(), &_mainCharacter->bounding_box()) == true && _Jafar->main_state() == "0")
					{
						_mainCharacter->BeBeaten();
						_mainCharacter->set_vx(_mainCharacter->vx() * 3);



					}

				}

				default: {}
				}
			}
		}
	}


	for (auto ab = _mainCharacter->bullet_list()->begin(); ab != _mainCharacter->bullet_list()->end(); ab++)
	{

		temp_apple_bullet_scene2 = *ab;
		if (temp_apple_bullet_scene2->Visbile() == true)
		{
			CollisionResult collisionIndex = CheckCollision(*ab, _Jafar);
			if (collisionIndex._collisionIndex<1.0f && collisionIndex._collisionIndex > 0.0f)
			{

				temp_apple_bullet_scene2->set_vx(collisionIndex._collisionIndex * temp_apple_bullet_scene2->vx());
				temp_apple_bullet_scene2->set_vy(collisionIndex._collisionIndex * temp_apple_bullet_scene2->vy());
				break;
			}
			if (collisionIndex._collisionIndex == 0.0f)
			{
				temp_apple_bullet_scene2->set_is_popping(true);
				temp_apple_bullet_scene2->state_manager()->setState("001");
				temp_apple_bullet_scene2->set_vx(0);
				temp_apple_bullet_scene2->set_vy(0);
				_soundAppleCollision->Play();


				magicExplosion->setPosition(temp_apple_bullet_scene2->x(), temp_apple_bullet_scene2->y());
				magicExplosion->setVisible(true);
				magicExplosion->set_state("001");

				if (_Jafar->is_immune() == 0.0f)
				{
					_Jafar->set_health(_Jafar->health() - 1);
					_Jafar->set_is_immune(30);
				}
				if (_Jafar->health() < 0)
				{
					_mainCharacter->setIsDying(true);
					_mainCharacter->set_curFace(GameObject::Face::RIGHT);
					if (_mainCharacter->CheckFlip())
						_mainCharacter->Flip();
					gameCase = GAMECASES::COMPLETE;
					if (_soundTheme->IsSoundPlaying())
						_soundTheme->Stop();
					_soundComplete->Play();

					MyCamera::GetInstance()->setPosition((MyCamera::GetInstance()->View().right - MyCamera::GetInstance()->View().left) / 2, MyCamera::GetInstance()->y());
					_mainCharacter->setPosition(MyCamera::GetInstance()->View().right - MyCamera::GetInstance()->View().left + 100, MyCamera::GetInstance()->y() + 50);
					_mainCharacter->setState("700");
					Abu->set_state("2");
					break;
				}




				break;

			}
		}

	}
	if (SimpleIntersect(_mainCharacter->sword(), &_Jafar->bounding_box()))
	{
		if (_Jafar->is_immune() == 0.0f)
		{
			_Jafar->set_health(_Jafar->health() - 1);
			_Jafar->set_is_immune(30);
			_Jafar->set_state("003");
			_Jafar->set_hand_state("3");
			_Jafar->setIsRepeating(false);
		}
	}
	quadtree->Clear();
	delete quadtree;

}
void Scene2::NormalizeAction()
{
	if (_mainCharacter->degree_state() != "3")
	{
		if (_mainCharacter->on_state_end() == true)
			_mainCharacter->set_on_state_end(false);
		_mainCharacter->set_degree_state("0");
	}
}

void Scene2::Key_Pressed(int KeyCode)
{

	if ((gameCase != GAMECASES::PLAYING && gameCase != GAMECASES::CHOSING) || (gameCase == GAMECASES::PLAYING && _mainCharacter->IsDying() == true))
		return;

	switch (KeyCode)
	{
	case DIK_P:
	{
		_mainCharacter->BeBeaten();
		break;
	}
	case DIK_Q:
	{
		_mainCharacter->setIsDying(true);
		_mainCharacter->set_curFace(GameObject::Face::RIGHT);
		if (_mainCharacter->CheckFlip())
			_mainCharacter->Flip();
		gameCase = GAMECASES::COMPLETE;
		if (_soundTheme->IsSoundPlaying())
			_soundTheme->Stop();
		_soundComplete->Play();

		MyCamera::GetInstance()->setPosition((MyCamera::GetInstance()->View().right - MyCamera::GetInstance()->View().left) / 2, MyCamera::GetInstance()->y());
		_mainCharacter->setPosition(MyCamera::GetInstance()->View().right - MyCamera::GetInstance()->View().left + 100, MyCamera::GetInstance()->y() + 50);
		_mainCharacter->setState("700");
		Abu->set_state("2");
		break;
		break;
	}

	case DIK_A:
		NormalizeAction();
		_mainCharacter->set_hand_state("2");
		_soundSlash->Play();
		break;
	case DIK_S:
		NormalizeAction();
		if (_mainCharacter->is_throwing() == false)
		{
			_mainCharacter->set_hand_state("1");
			_mainCharacter->FireApple();
		}

		break;
	case DIK_D:
		NormalizeAction();
		if (_mainCharacter->main_state() != "3" && _mainCharacter->sub_state() == "0")
		{
			_mainCharacter->set_sub_state("2");
			//_mainCharacter->setIsRepeating(false);
			_mainCharacter->setIsClimbing(false);
			_mainCharacter->set_vy(JUMPFORCE_SCENE2);
			_mainCharacter->set_jump_step_remaining(JUMP_STEP_SCENE2);
			//_mainCharacter->set_vy(JUMP_FORCE);
		}
		else
		{
			if (_mainCharacter->sub_state() == "5")
				_mainCharacter->setIsSwinging(false);
		}
		break;
	case DIK_LEFT:
		if (gameCase == GAMECASES::CHOSING)
		{
			_mainCharacter->setState("100");
			Abu->set_state("2");
			gameCase = GAMECASES::QUIT;
		}
		if (_mainCharacter->main_state() == "4" && _mainCharacter->curface() == GameObject::RIGHT)
		{
			_mainCharacter->set_last_face(GameObject::RIGHT);
			_mainCharacter->set_curFace(GameObject::LEFT);
			if (_mainCharacter->CheckFlip() == true)
				_mainCharacter->Flip();
		}
		break;
	case DIK_RIGHT:
		if (gameCase == GAMECASES::CHOSING)
		{
			_mainCharacter->setState("100");
			Abu->set_state("2");
			gameCase = GAMECASES::CONTINUE;
			if (Abu->CheckFlip() == true)
				Abu->Flip();
		}
		if (_mainCharacter->main_state() == "4" && _mainCharacter->curface() == GameObject::LEFT)
		{
			_mainCharacter->set_last_face(GameObject::LEFT);
			_mainCharacter->set_curFace(GameObject::RIGHT);
			if (_mainCharacter->CheckFlip() == true)
				_mainCharacter->Flip();
		}
		break;
	}

}

void Scene2::InputUpdate()
{
	if ((gameCase != GAMECASES::PLAYING && gameCase != GAMECASES::CHOSING) || (gameCase == GAMECASES::PLAYING && _mainCharacter->IsDying() == true))
		return;
	Poll_Keyboard();
	ProcessKeyboard();
	if (_mainCharacter->degree_state() == "6")
		return;
	if (Key_Hold(DIK_UP))
	{
		NormalizeAction();
		if (_mainCharacter->main_state() == "4")
		{
			_mainCharacter->set_vy(-CHARACTER_VX);
			return;
		}

		_mainCharacter->set_main_state("2");
		_mainCharacter->StopX();
		return;

	};

	if (Key_Hold(DIK_DOWN))
	{
		NormalizeAction();
		if (_mainCharacter->main_state() == "4")
		{
			_mainCharacter->set_vy(CHARACTER_VX);
			return;
		}
		_mainCharacter->StopX();
		_mainCharacter->set_main_state("3");
		return;
	}

	if (Key_Hold(DIK_LEFT))
	{
		NormalizeAction();
		if (_mainCharacter->main_state() != "4")
		{
			if (_mainCharacter->on_state_end() == true)
				_mainCharacter->set_on_state_end(false);
			_mainCharacter->set_main_state("1");

			if (_mainCharacter->main_state() == "1")
			{
				if (_mainCharacter->on_state_end() == false)
					_mainCharacter->set_prev_main_state("1");
			}
		}

		if (_mainCharacter->isClimbing() == false)
			_mainCharacter->set_vx(-CHARACTER_VX);
		else
			_mainCharacter->set_vx(0);
		return;
	}
	if (Key_Hold(DIK_RIGHT))
	{
		NormalizeAction();
		if (_mainCharacter->main_state() != "4")
		{
			if (_mainCharacter->on_state_end() == true)
				_mainCharacter->set_on_state_end(false);
			_mainCharacter->set_main_state("1");
			if (_mainCharacter->main_state() == "1")
			{
				if (_mainCharacter->on_state_end() == false)
					_mainCharacter->set_prev_main_state("1");
			}
		}

		if (_mainCharacter->isClimbing() == false)
			_mainCharacter->set_vx(CHARACTER_VX);
		else
			_mainCharacter->set_vx(0);
		return;
	}
	if (Key_Hold(DIK_Z))
	{
		return;
	}

	//to edit later
	if (_mainCharacter->main_state() != "4"
		|| (_mainCharacter->main_state() == "4" && _mainCharacter->isClimbing() == false))
	{
		_mainCharacter->set_main_state("0");
	}
	if (_mainCharacter->on_state_end() == false && _mainCharacter->prev_main_state() == "1" && _mainCharacter->hand_state() == "0" && _mainCharacter->sub_state() == "0" && _mainCharacter->vy() == 0 && _mainCharacter->isClimbing() == false && _mainCharacter->hand_state() == "0" && _mainCharacter->isSwinging() == false)
	{
		_mainCharacter->set_on_state_end(true);
		if (_mainCharacter->degree_state() == "0")
		{
			_mainCharacter->set_state("0001");
			_mainCharacter->set_degree_state("1");
		}
		_mainCharacter->set_prev_main_state("0");
	}
	if (_mainCharacter->on_state_end() == true && _mainCharacter->state_manager()->life_span() <= 0)
	{
		_mainCharacter->set_on_state_end(false);
		_mainCharacter->set_degree_state("0");
	}

	if (_mainCharacter->main_state() == "4" && _mainCharacter->isClimbing() == true)
		_mainCharacter->StopY();
	if (_mainCharacter->main_state() == "0" && _mainCharacter->sub_state() == "5"  && _mainCharacter->isSwinging() == true)
		_mainCharacter->StopY();

	_mainCharacter->StopX();

	return;
}

void Scene2::DisposablePhysicUpdate(float t)
{
	if (magicExplosion->state_manager()->life_span() == 0)
	{
		magicExplosion->set_state("000");
		magicExplosion->setVisible(false);
	}
	_mainCharacter->set_is_absorbed(false);
	for (auto i = _enemyBulletStarList->begin(); i != _enemyBulletStarList->end();)
	{
		temp_star_handle = *i;
		if (temp_star_handle->state_manager()->life_span() <= 0 || (find(_onScreenList->begin(), _onScreenList->end(), temp_star_handle) == _onScreenList->end()))
		{
			delete *i;
			i = _enemyBulletStarList->erase(i);
			_gameObjectList->remove(temp_star_handle);
			_onScreenList->remove(temp_star_handle);
		}
		else
		{
			bulletCollideScene2 = SimpleIntersect(&temp_star_handle->bounding_box(), &_mainCharacter->bounding_box());
			if (temp_star_handle->reach_target() == false)
			{
				if (temp_star_handle->x() > temp_star_handle->target_position().x)
					temp_star_handle->set_vx(-10);
				else temp_star_handle->set_vx(10);
				if (temp_star_handle->y() > temp_star_handle->target_position().y)
					temp_star_handle->set_vy(-5);
				else temp_star_handle->set_vy(5);
				if (temp_star_handle->x() > temp_star_handle->target_position().x - 10 &&
					temp_star_handle->target_position().x + 10 > temp_star_handle->x() &&
					temp_star_handle->y() > temp_star_handle->target_position().y - 5 &&
					temp_star_handle->target_position().y + 5 > temp_star_handle->y())
					temp_star_handle->set_reach_target(true);
			}
			else
			{
				if (temp_star_handle->x() > _mainCharacter->x())
					temp_star_handle->set_vx(-10);
				else temp_star_handle->set_vx(10);
				if (temp_star_handle->y() > _mainCharacter->y())
					temp_star_handle->set_vy(-5);
				else temp_star_handle->set_vy(5);
			}

			//to remove disposable thing out of screen when they are out of sight
			temp_star_handle->setPosition(temp_star_handle->x() + temp_star_handle->vx()* t, temp_star_handle->y() + temp_star_handle->vy()*t);
			if (bulletCollideScene2 == true)
			{
				if (_mainCharacter->is_immune() == 0.0f)
				{
					_mainCharacter->set_vx(_mainCharacter->vx() - temp_star_handle->vx() / 5);
					temp_star_handle->set_state("001");
					temp_star_handle->setIsRepeating(false);
					_mainCharacter->set_is_absorbed(true);
				}
			}
			i++;
		}
	}
	for (auto i = _enemyBulletFireList->begin(); i != _enemyBulletFireList->end();)
	{
		temp_bullet_scene2 = *i;
		if (temp_bullet_scene2->x() < 0 || temp_bullet_scene2->x() > mapinfo->Width)
		{
			delete *i;
			i = _enemyBulletFireList->erase(i);
			_gameObjectList->remove(temp_bullet_scene2);
		}
		else
		{
			bulletCollideScene2 = SimpleIntersect(&temp_bullet_scene2->bounding_box(), &_mainCharacter->bounding_box());
			if (temp_bullet_scene2->y() < FLOOR_Y)
				temp_bullet_scene2->set_vy(2);
			else temp_bullet_scene2->set_vy(0);
			//to remove disposable thing out of screen when they are out of sight
			temp_bullet_scene2->setPosition(temp_bullet_scene2->x() + temp_bullet_scene2->vx()* t, temp_bullet_scene2->y() + temp_bullet_scene2->vy()*t);
			if (bulletCollideScene2 == true)
			{
				if (_mainCharacter->is_immune() == 0.0f)
				{
					_mainCharacter->BeBeaten();
				}
			}
			i++;
		}
	}
}

void Scene2::JafarAI(GameObjectMove* jafar)
{
	if (_mainCharacter->x() < jafar->x())
		jafar->set_curFace(GameObject::LEFT);
	else jafar->set_curFace(GameObject::RIGHT);
	if (jafar->CheckFlip())
	{
		jafar->set_vx(-jafar->vx());
		jafar->Flip();
	}
	if (jafar->health() == 15)
	{
		jafar->set_main_state("1");
		if (jafar->played_sound_taunt() == false)
		{
			jafar->set_played_sound_taunt(true);
			PlaySound(_soundAnaconda);
		}
	}
	if (jafar->main_state() == "1")
	{
		jafar->set_state("101");
		jafar->set_hand_state("1");
		if (_enemyBulletStarList->size() == 0)
			_Jafar->set_is_throwing(false);
		jafar->setIsRepeating(false);
		if (jafar->is_throwing() == false && jafar->state_manager()->life_span() == 3)
		{
			if (drawOneOnAnime == false)
			{
				fireRemainToVisiblizeApple--;
				GameObject* temp_fire = new GameObject();
				FireBulletPrefab::Instantiate(temp_fire, jafar->x(), 438, jafar->curface());
				_enemyBulletFireList->push_back(temp_fire);
				//_gameObjectList->push_back(temp_fire);
				//_onScreenList->push_back(temp_fire);
				drawOneOnAnime = true;
			}

		}
		if (_Jafar->state_manager()->life_span() <= 0 && _Jafar->is_throwing() == false)
		{

			drawOneOnAnime = false;
			jafar->set_state("100");
			jafar->set_state("101");
		}

	}
	if (jafar->main_state() == "0")
	{
		jafar->set_state("001");
		jafar->set_hand_state("1");
		if (_enemyBulletStarList->size() == 0)
			_Jafar->set_is_throwing(false);
		jafar->setIsRepeating(false);
		//_markOdd++;
		if (jafar->state_manager()->life_span() <= 5 && _markOdd % 2 == 0 && jafar->state_manager()->life_span() >= 3 && jafar->hand_state() == "1" && jafar->is_throwing() == false)
		{
			temp_star = new StarBullet();
			StarBulletPrefab::Instantiate(temp_star, _Jafar->x(), _Jafar->y(), _Jafar->curface());
			temp_star->set_target_position(_mainCharacter->Position());
			_enemyBulletStarList->push_back(temp_star);
			_gameObjectList->push_back(temp_star);
			_onScreenList->push_back(temp_star);
			_disposableList->push_back(temp_star);
		}



		if (_Jafar->state_manager()->life_span() <= 0 && _Jafar->is_throwing() == false)
		{
			jafar->set_state("000");
			jafar->set_state("001");
		}

		if (_enemyBulletStarList->size() >= 20)
			_Jafar->set_is_throwing(true);
	}

}

void Scene2::PhysicsUpdate(float t)
{
	if (_mainCharacter->vy() == 0)
	{
		if (_mainCharacter->isSwinging() == false)
			_mainCharacter->set_sub_state("0");
	}
	if (_mainCharacter->vy() > 0)
	{
		_mainCharacter->set_sub_state("1");
	}
	JafarAI(_Jafar);
	_Jafar->PhysicUpdate(t);
	DisposablePhysicUpdate(t);
	if (_mainCharacter->on_state_end() == false)
	{
		_mainCharacter->setState(_mainCharacter->main_state() + _mainCharacter->sub_state() + _mainCharacter->hand_state());
	}
	_mainCharacter->set_vy(_mainCharacter->vy() + GRAVITY_SCENE2);
	if (_mainCharacter->IsDying() == false)
		CollisionDetect();
	else
	{
		_mainCharacter->set_vy(0);
		_mainCharacter->set_vx(0);
	}
	_mainCharacter->PhysicUpdate(t);
	if (fireRemainToVisiblizeApple == 0)
	{
		fireRemainToVisiblizeApple = 8;
		for (auto i = _appleList->begin(); i != _appleList->end(); i++)
		{
			temp_object_scene2 = *i;
			temp_object_scene2->set_state("000");
			temp_object_scene2->setVisible(true);
			temp_object_scene2->setDisappearing(false);
		}
	}
}

void Scene2::GraphicUpdate(float t)
{
	_mainCharacter->GraphicUpdate(t);
	MyCamera::GetInstance()->Update(t);


	if (_mainCharacter->IsDying() == true && (gameCase == GAMECASES::CHOSING || gameCase == GAMECASES::CONTINUE || gameCase == GAMECASES::QUIT))
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

			_mainCharacter->set_vx(-CHARACTER_VX);
			_mainCharacter->setPosition(_mainCharacter->x() - 3, _mainCharacter->y());
		}
		if (gameCase == GAMECASES::CONTINUE)
		{
			if (MyCamera::GetInstance()->View().right <= _mainCharacter->bounding_box().left)
			{

				gameCase = GAMECASES::PLAYING;
				_mainCharacter->WishContinue();
				Abu->set_state("0");
				return;
			}

			_mainCharacter->set_vx(CHARACTER_VX);
			_mainCharacter->setPosition(_mainCharacter->x() + 3, _mainCharacter->y());
		}

		_mainCharacter->setTranslation(D3DXVECTOR2(_mainCharacter->x() - MyCamera::GetInstance()->View().left, _mainCharacter->y() - MyCamera::GetInstance()->View().top));
		_mainCharacter->Render(false, true, true);
		Abu->setPosition(_mainCharacter->x() + 50, _mainCharacter->y());
		Abu->setTranslation(D3DXVECTOR2(Abu->x() - MyCamera::GetInstance()->View().left, Abu->y() - MyCamera::GetInstance()->View().top));
		Abu->Render();
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
		return;
	}



	if (_mainCharacter->IsDying() == true && gameCase == GAMECASES::COMPLETE)
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3ddev->StretchRect(completeBackground, NULL, backbuffer, NULL, D3DTEXF_NONE);
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
		sprite_handler->SetTransform(&old_matrix);
		Abu->GraphicUpdate(t);



		if (MyCamera::GetInstance()->View().left >= _mainCharacter->bounding_box().right)
		{
			gameCase = GAMECASES::WIN;
			if (_soundComplete->IsSoundPlaying())
				_soundComplete->Stop();
			_soundWin->Play();

			_mainCharacter->setPosition(_mainCharacter->x(), MyCamera::GetInstance()->y());
			_mainCharacter->setState("800");
		}
		_mainCharacter->setPosition(_mainCharacter->x() - 3, _mainCharacter->y());



		_mainCharacter->setTranslation(D3DXVECTOR2(_mainCharacter->x() - MyCamera::GetInstance()->View().left, _mainCharacter->y() - MyCamera::GetInstance()->View().top));
		_mainCharacter->Render(false, true, true);
		Abu->setPosition(_mainCharacter->x() - 50, _mainCharacter->y());
		Abu->setTranslation(D3DXVECTOR2(Abu->x() - MyCamera::GetInstance()->View().left, Abu->y() - MyCamera::GetInstance()->View().top));
		Abu->Render();
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
		return;
	}


	if (_mainCharacter->IsDying() == true && gameCase == GAMECASES::WIN)
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3ddev->StretchRect(winBackground, NULL, backbuffer, NULL, D3DTEXF_NONE);
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
		sprite_handler->SetTransform(&old_matrix);

		if (MyCamera::GetInstance()->View().right <= _mainCharacter->bounding_box().left)
		{
			gameCase = GAMECASES::END;
			_mainCharacter->setPosition(MyCamera::GetInstance()->x() + 50, MyCamera::GetInstance()->y() + 30);
			_mainCharacter->setState("900");
			_mainCharacter->setIsRepeating(false);
		}
		_mainCharacter->setPosition(_mainCharacter->x() + 3, _mainCharacter->y() - 1);

		_mainCharacter->setTranslation(D3DXVECTOR2(_mainCharacter->x() - MyCamera::GetInstance()->View().left, _mainCharacter->y() - MyCamera::GetInstance()->View().top));
		_mainCharacter->Render(false, true, true);

		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
		return;
	}



	if (_mainCharacter->IsDying() == true && gameCase == GAMECASES::END)
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3ddev->StretchRect(endBackground, NULL, backbuffer, NULL, D3DTEXF_NONE);
		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
		sprite_handler->SetTransform(&old_matrix);
		_mainCharacter->setTranslation(D3DXVECTOR2(_mainCharacter->x() - MyCamera::GetInstance()->View().left, _mainCharacter->y() - MyCamera::GetInstance()->View().top));
		_mainCharacter->Render(false, true, true);
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
		return;
	}




	if (_mainCharacter->IsDying() == true && gameCase == GAMECASES::PLAYING)
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		d3ddev->StretchRect(NULL, NULL, backbuffer, NULL, D3DTEXF_NONE);
		//reset jafar
		_mainCharacter->setAppleCount(10);
		_Jafar->set_state("0");
		_Jafar->set_main_state("0");
		_Jafar->set_played_sound_taunt(false);
		_Jafar->set_health(21);
		if (_soundTheme->IsSoundPlaying())
		{
			_soundTheme->Stop();
		}

		sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
		sprite_handler->SetTransform(&old_matrix);
		Abu->GraphicUpdate(t);

		_mainCharacter->setTranslation(D3DXVECTOR2(_mainCharacter->x() - MyCamera::GetInstance()->View().left, _mainCharacter->y() - MyCamera::GetInstance()->View().top));
		_mainCharacter->Render(false, true, true);


		Abu->setPosition(_mainCharacter->x() + 50, _mainCharacter->y());
		Abu->setTranslation(D3DXVECTOR2(Abu->x() - MyCamera::GetInstance()->View().left, Abu->y() - MyCamera::GetInstance()->View().top));
		Abu->Render();

		if (_mainCharacter->state_manager()->life_span() == 1 && _mainCharacter->Life() == 0 && gameCase == GAMECASES::PLAYING)
		{
			Abu->state_manager()->setState("1");
			gameCase = GAMECASES::CHOSING;
			_mainCharacter->setState("000");
		}
		sprite_handler->SetTransform(&old_matrix);
		sprite_handler->End();
		//stop rendering 
		d3ddev->EndScene();
		return;
	}



	if (_mainCharacter->degree_state() == "6")
		_mainCharacter->set_degree_state("0");
	//Render Everything
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);


	if (_soundTheme->IsSoundPlaying() == false)
		_soundTheme->Play(0, DSBPLAY_LOOPING);


	index = (index + 1) % 110;
	RECT srcRect;
	srcRect.top = animateBackground.top;
	srcRect.bottom = animateBackground.bottom;
	srcRect.left = animateBackground.left + index*speed;
	srcRect.right = animateBackground.right + index*speed;


	d3ddev->StretchRect(background, &srcRect, backbuffer, NULL, D3DTEXF_NONE);


	viewRect = MyCamera::GetInstance()->View();
	d3ddev->BeginScene();
	//start sprite handler 	
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	sprite_handler->SetTransform(&old_matrix);

	sprite_handler->Draw(mapETC, &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite_handler->Draw(mapETC, &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	_mainCharacter->setTranslation(D3DXVECTOR2(_mainCharacter->x() - MyCamera::GetInstance()->View().left, _mainCharacter->y() - MyCamera::GetInstance()->View().top));
	_mainCharacter->DrawBullet();
	_mainCharacter->Render(false, true, true);
	//_mainCharacter->RenderBounding(D3DCOLOR_RGBA(255, 255, 0, 70));
	for (auto i = _gameObjectList->begin(); i != _gameObjectList->end(); i++)
	{
		temp_object_scene2 = *i;
		temp_object_scene2->setAnchor(AnchorPoint::BOTTOM_MID);
		temp_object_scene2->setTranslation(D3DXVECTOR2(temp_object_scene2->x() - viewRect.left, temp_object_scene2->y() - viewRect.top));
		if (temp_object_scene2->sprite()->image())
		{
			temp_object_scene2->Render(false, true, true);
			temp_object_scene2->GraphicUpdate(t);
		}
		//temp_object_scene2->RenderBounding(D3DCOLOR_RGBA(255, 0, 255, 70));
	}
	for (auto i = _enemyBulletFireList->begin(); i != _enemyBulletFireList->end(); i++)
	{
		temp_object_scene2 = *i;
		temp_object_scene2->setAnchor(AnchorPoint::BOTTOM_MID);
		temp_object_scene2->setTranslation(D3DXVECTOR2(temp_object_scene2->x() - viewRect.left, temp_object_scene2->y() - viewRect.top));
		if (temp_object_scene2->sprite()->image())
		{
			temp_object_scene2->Render(false, true, true);
			temp_object_scene2->GraphicUpdate(t);
			//temp_object_scene2->RenderBounding(D3DCOLOR_RGBA(255, 255, 0, 70));
		}
	}
	_UI->Render(_mainCharacter->health(), _mainCharacter->Life(), _mainCharacter->appleCount(), _mainCharacter->DiamondCount(), _mainCharacter->Score());


	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();

}

list<GameObject*>* Scene2::OnScreenDetect()
{
	Quadtree* quadtree = Quadtree::CreateQuadtree(0, 0, mapinfo->Width, mapinfo->Height);
	list<GameObject*>* return_object_list = new list<GameObject*>();
	quadtree->Retrieve(return_object_list, MyCamera::GetInstance());
	quadtree->Clear();
	delete quadtree;
	return return_object_list;
}


void Scene2::Game_Run(HWND hwnd, int)
{
	GameTime::GetInstance()->StartCounter();
	InputUpdate();

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	DWORD now = GetTickCount();
	//this keeps the game running at a steady frame rate
	float t = now - startScene2;
	if (t >= 1000 / FPS)
	{

		//reset timing
		startScene2 = now;
		if (t < FIXED_TIME)
			Sleep(FIXED_TIME - t);
		_onScreenList = OnScreenDetect();
		if (_mainCharacter->IsDying() == false || (_mainCharacter->IsDying() == true && _mainCharacter->Life() == 0))
		{
			PhysicsUpdate(FIXED_TIME);
		}
		GraphicUpdate(FIXED_TIME);
		for (auto i = _onScreenList->begin(); i != _onScreenList->end();)
		{
			i = _onScreenList->erase(i);
		}
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

void Scene2::LoadListObjectXml(char* xmlpath)
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
			if (name == "Ground" || name == "Wall" || name == "Pedestal")
			{
				anchorTransformY = atoi(object.attribute("height").value());
			}
			anchorTransformX = atoi(object.attribute("width").value()) / 2;

			GameObject * anObject;
			switch (idName)
			{
			case 0:
				anObject = new GameObject();
				ApplePrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				_appleList->push_back(anObject);
				break;
			case 1:
				anObject = new GameObject();
				GroundPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				anObject->setAnchor(AnchorPoint::BOTTOM_MID);
				break;
			case 2:
				anObject = new GameObject();
				WallPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				anObject->setAnchor(AnchorPoint::BOTTOM_MID);
				break;
			case 3:
				anObject = new GameObject();
				FireGroundPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				anObject->setAnchor(AnchorPoint::TOP_MID);
				break;
			default:
				anObject = new GameObject();
				break;
			}



			anObject->set_bounding_box(CalculateBoundingBox(anObject->x(), anObject->y(), anObject->width(), anObject->height(), anObject->anchor()));
			(CalculateBoundingBox(anObject->x(), anObject->y(), anObject->width(), anObject->height(), anObject->anchor()));
			_gameObjectList->push_back(anObject);
		}
	}

}

void Scene2::Game_End(HWND hwnd)
{
	Game::Game_End(hwnd);
	delete temp_apple_bullet_scene2;
	//delete temp_burnfx_scene2;
	delete _mainCharacter;

}

Scene2::Scene2()
{
}


Scene2::~Scene2()
{
}

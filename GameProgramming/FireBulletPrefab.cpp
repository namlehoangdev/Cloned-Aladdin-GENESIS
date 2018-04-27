#include "FireBulletPrefab.h"


void FireBulletPrefab::Instantiate(GameObject* gameObj, int x, int y, GameObject::Face face)
{
	gameObj->set_name("FireBullet");
	gameObj->setSprite(new Sprite("Res\\SceneBoss\\Jafar.png", 1, 1));
	gameObj->set_state_manager(new StateManager("Res\\SceneBoss\\FireBulletXML.xml"));
	gameObj->state_manager()->AddToDictState("000", "Move");
	gameObj->setPosition(x, y);
	if (face == GameObject::RIGHT)
		gameObj->set_vx(9);
	else
	{
		gameObj->set_vx(-9);
		gameObj->Flip();
	}
	gameObj->setIsRepeating(true);
	gameObj->set_state("000");
}

FireBulletPrefab::FireBulletPrefab()
{
}


FireBulletPrefab::~FireBulletPrefab()
{
}

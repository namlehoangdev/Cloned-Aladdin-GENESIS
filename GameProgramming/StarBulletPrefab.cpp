#include "StarBulletPrefab.h"

void StarBulletPrefab::Instantiate(GameObject* gameObj, int x, int y, GameObject::Face face)
{
	gameObj->set_name("StarBullet");
	gameObj->setSprite(new Sprite("Res\\SceneBoss\\Jafar.png", 1, 1));
	gameObj->set_state_manager(new StateManager("Res\\SceneBoss\\StarBullet.xml"));
	gameObj->setPosition(x, y);
	gameObj->state_manager()->AddToDictState("000", "Fly");
	gameObj->state_manager()->AddToDictState("001", "Pop");
	if (face == GameObject::RIGHT)
		gameObj->set_vx(5);
	else gameObj->set_vx(-5);
	gameObj->setIsRepeating(true);
	gameObj->set_state("000");
}

StarBulletPrefab::StarBulletPrefab()
{
}


StarBulletPrefab::~StarBulletPrefab()
{
}

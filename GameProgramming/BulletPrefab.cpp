#include "BulletPrefab.h"


void BulletPrefab::Instantiate(GameObject* gameObject, char* category, int x, int y, GameObject::Face direction)
{
	gameObject->set_state_manager(new StateManager("Res\\BulletXML.xml"));
	gameObject->setSprite(new Sprite("Res\\Bullet.png", 0, 0));
	gameObject->state_manager()->AddToDictState("000", category);
	gameObject->state_manager()->setState("000");
	gameObject->setPosition(x, y);
	if (direction == GameObject::RIGHT)
		gameObject->set_vx(BULLET_PREFAB_VX);
	if (direction == GameObject::LEFT)
		gameObject->set_vx(-BULLET_PREFAB_VX);
	gameObject->set_vy(0);

}

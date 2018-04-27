#include "PotPrefab.h"

#define ACCE_Y 1.0f
void PotPrefab::Instantiate(Pot* gameObject, float x, float y, int breakpoint)
{
	gameObject->set_name("Pot");
	gameObject->set_break_point(breakpoint);
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Bullet.png", 0, 0));
	gameObject->set_state_manager(new StateManager("Res\\PotBulletXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "PotFall");
	gameObject->state_manager()->AddToDictState("001", "PotBroken");
	gameObject->set_state("000");
	gameObject->setAnchor(BOTTOM_MID);
	gameObject->setIsRepeating(true);
	gameObject->set_vx(0);
	gameObject->set_vy(0);

}

PotPrefab::PotPrefab()
{
}


PotPrefab::~PotPrefab()
{
}

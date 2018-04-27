#include "EnemyHandPrefab.h"

void EnemyHandPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height, int xMin, int xMax)
{
	gameObject->set_health(1);
	gameObject->set_name("EnemyHand");
	gameObject->setPosition(x, y);
	gameObject->set_min_x(xMin);
	gameObject->set_max_x(xMax);
	gameObject->setSprite(new Sprite("Res\\Enemy2.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyHandXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "None");
	gameObject->state_manager()->AddToDictState("001", "EnemyHandSlash"); 
	gameObject->state_manager()->setState("000");
	gameObject->set_hand_state("0");
}

EnemyHandPrefab::EnemyHandPrefab()
{
}


EnemyHandPrefab::~EnemyHandPrefab()
{
}

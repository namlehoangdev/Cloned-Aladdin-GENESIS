#include "EnemyThinPrefab.h"

void EnemyThinPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height, int xMin, int xMax)
{
	gameObject->set_name("EnemyThin");
	gameObject->set_min_x(xMin);
	gameObject->set_max_x(xMax);
	gameObject->set_health(2);
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy1.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyThinXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "EnemyThinIdle");
	gameObject->state_manager()->AddToDictState("001", "EnemyThinRun");
	gameObject->state_manager()->AddToDictState("002", "EnemyThinSlash");
	gameObject->state_manager()->AddToDictState("003", "EnemyThinBeaten");
	gameObject->set_main_state("0");
	gameObject->set_sub_state("0");
	gameObject->set_hand_state("0");
	gameObject->state_manager()->setState("000");
} 

EnemyThinPrefab::EnemyThinPrefab()
{
}


EnemyThinPrefab::~EnemyThinPrefab()
{
}

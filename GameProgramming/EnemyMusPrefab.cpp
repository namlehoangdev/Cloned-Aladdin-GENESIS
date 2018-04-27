#include "EnemyMusPrefab.h"

void EnemyMusPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height, int xMin, int xMax)
{
	gameObject->set_name("EnemyMus");
	gameObject->set_health(2);
	gameObject->set_min_x(xMin);
	gameObject->set_max_x(xMax);
	gameObject->setPosition(x, y);
	//gameObject->set_vx(-10);
	gameObject->setSprite(new Sprite("Res\\Enemy1.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyMusXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "EnemyMusTaunt");
	gameObject->state_manager()->AddToDictState("001", "EnemusRun");
	gameObject->state_manager()->AddToDictState("002", "EnemusHeavyAttack"); 
	gameObject->state_manager()->AddToDictState("005", "EnemusSlash");
	gameObject->state_manager()->AddToDictState("004", "EnemusHot"); 
	gameObject->state_manager()->AddToDictState("003", "EnemyMusBeaten");
	gameObject->set_main_state("0");
	gameObject->set_sub_state("0");
	gameObject->set_hand_state("0");
	gameObject->state_manager()->setState("000");
}

EnemyMusPrefab::EnemyMusPrefab()
{
}


EnemyMusPrefab::~EnemyMusPrefab()
{
}

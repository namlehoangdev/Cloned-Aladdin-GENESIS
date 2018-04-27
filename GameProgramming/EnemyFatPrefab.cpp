#include "EnemyFatPrefab.h"
 
void EnemyFatPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height, int xMin, int xMax)
{ 
	gameObject->set_name("EnemyFat");
	gameObject->set_reach_limit(false);
	gameObject->set_health(2);
	gameObject->setPosition(x, y);
	gameObject->set_min_x(xMin);
	gameObject->set_max_x(xMax);
	gameObject->set_vx(-5);
	gameObject->setSprite(new Sprite("Res\\Enemy1.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyFatXML.xml")); 
	gameObject->state_manager()->AddToDictState("000", "EnemyFatIdle");
	gameObject->state_manager()->AddToDictState("001", "EnemyFatRun");
	gameObject->state_manager()->AddToDictState("002", "EnemyFatSlash");
	gameObject->state_manager()->AddToDictState("003", "EnemyFatBeaten");
	gameObject->set_main_state("0");
	gameObject->set_hand_state("0");
	gameObject->set_sub_state("0");
	gameObject->state_manager()->setState("000");  
	gameObject->set_attack_turn_remain(4);
}

EnemyFatPrefab::EnemyFatPrefab()
{
}


EnemyFatPrefab::~EnemyFatPrefab()
{
}

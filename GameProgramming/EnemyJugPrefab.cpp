#include "EnemyJugPrefab.h"

void EnemyJugPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height, int xMin, int xMax)
{
	gameObject->set_health(2);
	gameObject->set_curFace(GameObject::LEFT);
	gameObject->set_name("EnemyJug");
	gameObject->set_min_x(xMin);
	gameObject->set_max_x(xMax);
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy3.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyJugXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "EnemyJugIdle");  
	gameObject->state_manager()->AddToDictState("002", "EnemyJugSlash1");
	gameObject->state_manager()->AddToDictState("003", "EnemyJugSlash2"); 
	gameObject->state_manager()->setState("000");
	gameObject->Flip();
}

EnemyJugPrefab::EnemyJugPrefab()
{
}


EnemyJugPrefab::~EnemyJugPrefab()
{
}

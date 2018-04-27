#include "EnemyJarPrefab.h"

void EnemyJarPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height, int xMin, int xMax)
{
	gameObject->set_name("EnemyJar");
	gameObject->set_health(2);
	gameObject->set_min_x(xMin);
	gameObject->set_max_x(xMax);
	gameObject->setIsRepeating(false);
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy3.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyJarXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "EnemyJarIdle");
	gameObject->state_manager()->AddToDictState("001", "EnemyJarRun");
	gameObject->state_manager()->AddToDictState("002", "EnemyJarSlash");
	gameObject->state_manager()->AddToDictState("003", "EnemyJarIdle");
	gameObject->state_manager()->setState("000");
	gameObject->Flip();
}

EnemyJarPrefab::EnemyJarPrefab()
{
}


EnemyJarPrefab::~EnemyJarPrefab()
{
}

#include "CheckpointJarPrefab.h"


void CheckpointJarPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("CheckpointJar");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Items.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\CheckpointJarXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "Idle");
	gameObject->state_manager()->AddToDictState("1", "Eaten");
	gameObject->state_manager()->setState("0");
	gameObject->setAnimaDelay(2);
}

CheckpointJarPrefab::CheckpointJarPrefab()
{
}


CheckpointJarPrefab::~CheckpointJarPrefab()
{
}

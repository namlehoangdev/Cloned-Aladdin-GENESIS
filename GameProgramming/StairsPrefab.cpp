#include "StairsPrefab.h"
#include "GameObject.h"


void StairsPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Stairs");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Stairs.png", width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\Stairs.xml"));
	gameObject->state_manager()->AddToDictState("000", "Stairs");
	gameObject->state_manager()->setState("000");*/
}

StairsPrefab::StairsPrefab()
{
}


StairsPrefab::~StairsPrefab()
{
}

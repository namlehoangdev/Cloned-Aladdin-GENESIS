#include "TriggerPrefab.h"
#include "GameObject.h"


void TriggerPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Trigger");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\blank.png", width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\Trigger.xml"));
	gameObject->state_manager()->AddToDictState("000", "Trigger");
	gameObject->state_manager()->setState("000");*/
}

TriggerPrefab::TriggerPrefab()
{
}


TriggerPrefab::~TriggerPrefab()
{
}

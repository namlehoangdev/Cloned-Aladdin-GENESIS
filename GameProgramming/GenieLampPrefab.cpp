#include "GenieLampPrefab.h"


void GenieLampPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("GenieLamp");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Items.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\GenieLampXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "Idle");
	gameObject->state_manager()->AddToDictState("1", "Eaten");
	gameObject->state_manager()->setState("0");
	gameObject->setAnimaDelay(2);
}

GenieLampPrefab::GenieLampPrefab()
{
}


GenieLampPrefab::~GenieLampPrefab()
{
}

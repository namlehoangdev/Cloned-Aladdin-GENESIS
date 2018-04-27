#include "HeartPrefab.h"
 

void HeartPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Heart");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Items.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\HeartXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "Idle");
	gameObject->state_manager()->AddToDictState("1", "Eaten");
	gameObject->state_manager()->AddToDictState("1", "Explore"); 
	gameObject->state_manager()->setState("0");
	gameObject->setAnimaDelay(2); 
}
 
HeartPrefab::HeartPrefab()
{
}


HeartPrefab::~HeartPrefab()
{
}

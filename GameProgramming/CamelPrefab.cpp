#include "CamelPrefab.h"

void CamelPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height)
{
	gameObject->set_health(9);
	gameObject->set_name("Camel");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Camel.png", width,height));
	gameObject->set_state_manager(new StateManager("Res\\CamelXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "CamelIdle"); 
	gameObject->state_manager()->AddToDictState("001", "CamelBeaten");
	gameObject->state_manager()->setState("000");
	gameObject->setAnimaDelay(0.1);
	gameObject->setIsRepeating(false);
}

CamelPrefab::CamelPrefab()
{
}


CamelPrefab::~CamelPrefab()
{
}

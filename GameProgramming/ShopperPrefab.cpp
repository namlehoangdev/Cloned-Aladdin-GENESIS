#include "ShopperPrefab.h"
#include "GameObject.h"


void ShopperPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{ 
	gameObject->set_name("Shopper");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Shopper.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\ShopperXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "Idle1");
	gameObject->state_manager()->AddToDictState("1", "Idle2");
	gameObject->state_manager()->AddToDictState("2", "Idle3");
	gameObject->state_manager()->AddToDictState("3", "ShopperOpen");
	gameObject->state_manager()->setState("0"); 
	gameObject->setIsRepeating(false);
}


ShopperPrefab::ShopperPrefab()
{
}


ShopperPrefab::~ShopperPrefab()
{
}

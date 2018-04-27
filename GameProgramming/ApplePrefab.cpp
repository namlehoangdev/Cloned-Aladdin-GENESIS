#include "ApplePrefab.h"
#include "GameObject.h"


void ApplePrefab::Instantiate(GameObject* gameObject,float x, float y,int width, int height)
{
	gameObject->set_name("Apple");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Items.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\AppleXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "Idle");
	gameObject->state_manager()->AddToDictState("1", "Explore");
	gameObject->state_manager()->setState("000"); 
	
}

ApplePrefab::ApplePrefab()
{
}


ApplePrefab::~ApplePrefab()
{
}

#include "AbuPrefab.h"
#include "GameObject.h"


void AbuPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Abu");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Abu.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\AbuXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "Encorage");
	gameObject->state_manager()->AddToDictState("1", "Idle"); 
	gameObject->state_manager()->AddToDictState("2", "Run"); 
	gameObject->state_manager()->setState("0");
	gameObject->setAnchor(BOTTOM_MID);
} 

AbuPrefab::AbuPrefab()
{
}


AbuPrefab::~AbuPrefab()
{
}

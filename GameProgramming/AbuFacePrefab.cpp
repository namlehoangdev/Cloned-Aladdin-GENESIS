#include "AbuFacePrefab.h"


void AbuFacePrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("AbuFace");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Items.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\AbuFaceXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "Idle");
	gameObject->state_manager()->AddToDictState("1", "Explore");
	gameObject->state_manager()->setState("0");
	gameObject->setAnimaDelay(2);
}

AbuFacePrefab::AbuFacePrefab()
{
}


AbuFacePrefab::~AbuFacePrefab()
{
}

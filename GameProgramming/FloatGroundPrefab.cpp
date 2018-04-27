#include "FloatGroundPrefab.h"
#include "GameObject.h"


void FloatGroundPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("FloatGround");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\FloatGround.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\FloatGroundXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "New");
	gameObject->state_manager()->AddToDictState("001", "Broken");
	gameObject->state_manager()->setState("000");
	gameObject->set_is_hitted(false);
	gameObject->setIsRepeating(true);
}

FloatGroundPrefab::FloatGroundPrefab()
{
}


FloatGroundPrefab::~FloatGroundPrefab()
{
}

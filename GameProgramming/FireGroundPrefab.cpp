#include "FireGroundPrefab.h"
#include "GameObject.h"


void FireGroundPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("FireGround");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\FireGround.png", width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\FireGround.xml"));
	gameObject->state_manager()->AddToDictState("000", "FireGround");
	gameObject->state_manager()->setState("000");*/
}

FireGroundPrefab::FireGroundPrefab()
{
}


FireGroundPrefab::~FireGroundPrefab()
{

}

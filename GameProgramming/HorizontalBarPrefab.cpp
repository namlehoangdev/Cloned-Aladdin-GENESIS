#include "HorizontalBarPrefab.h"
#include "GameObject.h"


void HorizontalBarPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("HorizontalBar");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\blank.png", width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\HorizontalBar.xml"));
	gameObject->state_manager()->AddToDictState("000", "HorizontalBar");
	gameObject->state_manager()->setState("000");*/	   
}

HorizontalBarPrefab::HorizontalBarPrefab()
{
}


HorizontalBarPrefab::~HorizontalBarPrefab()
{
}

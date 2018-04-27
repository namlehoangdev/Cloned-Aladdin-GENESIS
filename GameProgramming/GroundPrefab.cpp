#include "GroundPrefab.h"
#include "GameObject.h"


void GroundPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Ground");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\blank.png", width, height));
}

GroundPrefab::GroundPrefab()
{
}


GroundPrefab::~GroundPrefab()
{
}

#include "RopePrefab.h"
#include "GameObject.h"


void RopePrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Rope");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\blank.png", width, height));
}

RopePrefab::RopePrefab()
{
}


RopePrefab::~RopePrefab()
{
}

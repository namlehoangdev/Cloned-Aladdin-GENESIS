#include "WallPrefab.h"
#include "GameObject.h"


void WallPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Wall");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Wall.png", width, height));
}

WallPrefab::WallPrefab()
{
}


WallPrefab::~WallPrefab()
{
}

#include "CeilingPrefab.h"


void CeilingPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Ceiling");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\blank.png", width, height));
}

CeilingPrefab::CeilingPrefab()
{
}


CeilingPrefab::~CeilingPrefab()
{
}

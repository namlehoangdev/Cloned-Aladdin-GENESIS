#include "ShopperTextPrefab.h"
#include "GameObject.h"


void ShopperTextPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("ShopperText");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\ShopperText.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\ShopperTextXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "FindMore"); 
	gameObject->state_manager()->AddToDictState("1", "MakeDeal"); 
	gameObject->state_manager()->AddToDictState("2", "FindMoreDisappear"); 
	gameObject->state_manager()->AddToDictState("3", "MakeDealDisappear"); 
	gameObject->state_manager()->setState("0");
	gameObject->setAnchor(BOTTOM_MID);
	gameObject->setVisible(false);

}
 
ShopperTextPrefab::ShopperTextPrefab()
{
}


ShopperTextPrefab::~ShopperTextPrefab()
{
}

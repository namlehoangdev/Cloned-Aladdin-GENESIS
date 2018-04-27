#include "SpringBoardPrefab.h"
#include "GameObject.h"


void SpringBoardPrefab::Instantiate(GameObject* gameObject, float x,float y,int width, int height)
{
	gameObject->set_name("SpringBoard");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\SpringBoard.png",width, height));
	gameObject->set_state_manager(new StateManager("Res\\SpringBoardXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "Still");
	gameObject->state_manager()->AddToDictState("001", "JumpedOn");
	gameObject->state_manager()->setState("000");
	gameObject->setAnchor(AnchorPoint::MID_LEFT);

}

SpringBoardPrefab::SpringBoardPrefab()
{
}


SpringBoardPrefab::~SpringBoardPrefab()
{
}

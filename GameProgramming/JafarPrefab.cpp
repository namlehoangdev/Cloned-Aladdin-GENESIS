#include "JafarPrefab.h"


void JafarPrefab::Instantiate(GameObjectMove* jafar, int x, int y)
{
	jafar->set_name("Jafar");
	jafar->set_health(21);
	jafar->setSprite(new Sprite("Res\\SceneBoss\\BossSprite.png", 68, 64));
	jafar->set_state_manager(new StateManager("Res\\SceneBoss\\JarfarXML.xml"));
	
	jafar->state_manager()->AddToDictState("000", "HumanIdle");
	jafar->state_manager()->AddToDictState("001", "HumanAttack");
	jafar->state_manager()->AddToDictState("100", "AnacondaIdle");
	jafar->state_manager()->AddToDictState("101", "AnacondaAttack");
	jafar->set_state("000");
	jafar->set_main_state("0");
	jafar->set_sub_state("0");
	jafar->set_hand_state("0");
	jafar->setPosition(x, y);
	jafar->Flip();

}

JafarPrefab::JafarPrefab()
{
}


JafarPrefab::~JafarPrefab()
{
}

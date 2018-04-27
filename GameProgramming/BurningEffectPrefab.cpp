#include "BurningEffectPrefab.h"


void BurningEffectPrefab::Instantiate(GameObject* obj)
{
	obj->set_name("BurningEffect");
	obj->setSprite(new Sprite("Res\\BurningEffect.png", 10, 10));
	obj->set_state_manager(new StateManager("Res\\BurningEffectXML.xml"));
	obj->state_manager()->AddToDictState("000", "Empty");
	obj->state_manager()->AddToDictState("001", "Burning");
	obj->setPosition(0, 0);
	obj->set_state("001");
	obj->setVisible(false);
	obj->setAnchor(BOTTOM_MID);
	
	obj->setIsRepeating(true);
	obj->setAnimaDelay(2);
}

#include "ExplosionPrefab.h"
#include "StateManager.h"
#include "sprite.h"


void ExplosionPrefab::Instantiate(GameObject* obj, int x, int y)
{
	obj->set_name("Explosion");
	obj->setSprite(new Sprite("Res\\enemy_explosion.png", 1, 1));
	obj->set_state_manager(new StateManager("Res\\ExplosionXML.xml"));
	obj->state_manager()->AddToDictState("000", "Exploding");
	obj->state_manager()->AddToDictState("001", "Empty");
	obj->setPosition(x, y);
	obj->setVisible(false);
	obj->setIsRepeating(false);
	obj->setAnchor(BOTTOM_MID);
	obj->set_state("001");
	obj->setAnimaDelay(0.1);
}

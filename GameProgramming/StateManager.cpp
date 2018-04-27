#include "StateManager.h"


int StateManager::STATEMANAGER_CREATED = 0;
int StateManager::STATEMANAGER_DELETED = 0;

StateManager::StateManager()
{
	STATEMANAGER_CREATED++;
	_curState = State();
	_lifeSpan = 0;
}
StateManager::~StateManager()
{
	STATEMANAGER_DELETED++;
}

void StateManager::AddToDictState(string key, string data)
{
	_dictState[key] = data;
	return;
}

StateManager::StateManager(char* xmlpath)
{
	STATEMANAGER_CREATED++;
	xml_document fileXml;
	xml_parse_result result = fileXml.load_file(xmlpath);
	xml_node root = fileXml.child("Animations");

	for (xml_node nodeAnimation = root.first_child(); nodeAnimation; nodeAnimation = nodeAnimation.next_sibling())
	{

		string name = nodeAnimation.attribute("name").value();
		int animaDelay = 1;
		animaDelay = nodeAnimation.attribute("delay").as_int();

		vector <RECT> srcRect; 
		for (xml_node nodeRec = nodeAnimation.first_child(); nodeRec; nodeRec = nodeRec.next_sibling())
		{
			RECT rect;
			rect.top = atoi(nodeRec.attribute("y").value());
			rect.left = atoi(nodeRec.attribute("x").value());
			rect.bottom = atoi(nodeRec.attribute("h").value()) + rect.top;
			rect.right = atoi(nodeRec.attribute("w").value()) + rect.left;
			srcRect.push_back(rect); 
		}
		_mapState[name] = State(name, srcRect,animaDelay);	
	}
}


void StateManager::setState(string stateCode)
{
	if (_dictState[stateCode] != "")
	{	
		string targetState = _dictState[stateCode];
		_lifeSpan = _mapState[targetState].getListRect().size();
		_curState = _mapState[targetState];
	}

}


State StateManager::getStateByCode(string stateCode)
{
	if (_dictState[stateCode] == "")
		return _curState;
	return _mapState[(_dictState[stateCode])];
}

void StateManager::setLastState(string lastStateCode)
{
	if (_dictState[lastStateCode] != "")
	{
		string targetState = _dictState[lastStateCode];
		_lastState = _mapState[targetState];
	}
}



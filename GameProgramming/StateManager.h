#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_
#include <map>
#include "State.h"
#include <vector>
using namespace std;

class StateManager
{
private:
	State _curState;
	State _lastState;
	int _lifeSpan;
public:
	int life_span() const
	{
		return _lifeSpan;
	}

	void set_life_span(int life_span)
	{
		_lifeSpan = life_span;
	}

	// used to check press state
	State curState() const
	{
		return _curState;
	}

	State lastState() const
	{
		return _lastState;
	}


private:
	//Sta	te_Name _state;

	map<string, string> _dictState;
	map<string, State> _mapState;

public:
	map<string, string> dict_state() const
	{
		return _dictState;
	}

	void set_dict_state(const map<string, string>& pairs)
	{
		_dictState = pairs;
	}
  
public:
	StateManager();
	~StateManager();
	//Add an element to dictstate
	void AddToDictState(string key, string data);
	StateManager(char* xmlpath);
	void setState(string stateCode);
	State getStateByCode(string stateCode);

	void setLastState(string lastStateCode);
	static int STATEMANAGER_CREATED;
	static int STATEMANAGER_DELETED;
};

#endif // !_STATE_MANAGER_H_

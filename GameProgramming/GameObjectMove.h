#pragma once
#include "GameObject.h";
class GameObjectMove :public GameObject
{
protected:
	//mark as standstill
	bool _isStandStill;
	bool _playedSoundTaunt;
public:
	bool played_sound_taunt() const
	{
		return _playedSoundTaunt;
	}

	void set_played_sound_taunt(bool played_sound_taunt)
	{
		_playedSoundTaunt = played_sound_taunt;
	}

private:
	GameObject* _weaponObj;
	bool _reachLimit;
public:
	bool reach_limit() const
	{
		return _reachLimit;
	}

	void set_reach_limit(bool reach_limit)
	{
		_reachLimit = reach_limit;
	}

private:
	//attack turn remain
	int _attackTurnRemain;
public:
	bool is_stand_still() const
	{
		return _isStandStill;
	}

	void set_is_stand_still(bool is_stand_still)
	{
		_isStandStill = is_stand_still;
	}

	int attack_turn_remain() const
	{
		return _attackTurnRemain;
	}

	void set_attack_turn_remain(int attack_turn_remain)
	{
		_attackTurnRemain = attack_turn_remain;
	}

protected:
	int _distanceFromMain;
	int _minX, _maxX;
public:
	int min_x() const
	{
		return _minX;
	}

	void set_min_x(int min_x)
	{
		_minX = min_x;
	}

	int max_x() const
	{
		return _maxX;
	}

	void set_max_x(int max_x)
	{
		_maxX = max_x;
	}
	int distance_from_main() const
	{
		return _distanceFromMain;
	}

	void set_distance_from_main(int distance_from_main)
	{
		_distanceFromMain = distance_from_main;
	}

	GameObject* weapon_obj() const
	{
		return _weaponObj;
	}

	void set_weapon_obj(GameObject* game_object)
	{
		_weaponObj = game_object;
	}

protected:
	int _health;
	bool _isThrowing;
public:
	bool is_throwing() const
	{
		return _isThrowing;
	}

	void set_is_throwing(bool is_throwing)
	{
		_isThrowing = is_throwing;
	}

protected:
	float _isImmune;
	string _mainState, _subState, _handState;
public:
	string hand_state() const
	{
		return _handState;
	}

	void set_hand_state(const string& cs)
	{
		_handState = cs;
	}

	string main_state() const
	{
		return _mainState;
	}

	void set_main_state(const string& cs)
	{
		_mainState = cs;
	}

	string sub_state() const
	{
		return _subState;
	}

	void set_sub_state(const string& cs)
	{
		_subState = cs;
	}
protected:
	RECT* _sword;

public:
	virtual void GraphicUpdate(float t) override;
	virtual void PhysicUpdate(float t);
	RECT* sword() const
	{
		return _sword;
	}

	void set_sword(RECT* tag_rect)
	{
		_sword = tag_rect;
	}
	void CalSword();
	void DelSword();
public:
	float is_immune() const
	{
		return _isImmune;
	}
	void set_is_immune(float is_immune)
	{
		_isImmune = is_immune;
	}
	GameObjectMove();
	~GameObjectMove();
	int health() ;
	void virtual set_health(int newHealth);
	static int NUMBER_GOMOVE_CREATED;
	static int NUMBER_GOMOVE_DELETED;
};


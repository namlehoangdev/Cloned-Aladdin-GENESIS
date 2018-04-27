#pragma once
#ifndef __GAME_TIME__
#define __GAME_TIME__

#include<Windows.h>
class GameTime
{
private:
	GameTime();
	LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockrate;
	static GameTime* mInstance;

public:
	void StartCounter();
	float GetCounter();
	static GameTime* GetInstance();


	~GameTime();
};
#endif // !__GAME_TIME__


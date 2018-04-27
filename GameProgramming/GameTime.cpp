#include "GameTime.h"

GameTime* GameTime::mInstance = nullptr;

GameTime::GameTime()
{
}

void GameTime::StartCounter()
{
	if (!QueryPerformanceCounter(&mClockrate))
	{
		return;
	}
	QueryPerformanceCounter(&mStartTime);
}

float GameTime::GetCounter()
{
	QueryPerformanceCounter(&mEndTime);

	mDelta.QuadPart = mEndTime.QuadPart - mStartTime.QuadPart;
	return (float)mDelta.QuadPart / (float)mClockrate.QuadPart;


}

GameTime * GameTime::GetInstance()
{
	if (!mInstance)
		mInstance = new GameTime();
	return mInstance;
}


GameTime::~GameTime()
{
}

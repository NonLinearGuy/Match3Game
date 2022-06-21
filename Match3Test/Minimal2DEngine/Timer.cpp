//Declaration header
#include"Timer.h"


//Exposing namespace
using namespace std::chrono;




namespace Minimal2DEngine
{


	//Private functions


	double Timer::InSeconds(mClock::duration pDuration) const
	{
		return (duration_cast<microseconds>(pDuration).count() / 1000000.0);
	}


	Timer::Timer()
	{
		Init();
	}



	//Public functions
	
	void Timer::Init()
	{
		mLast = mClock::now();
		mLastTime = mClock::now();

		mCounter = 0;
		mFPS = 0;
	}


	void Timer::Update()
	{

		//Updating mElapsedTime
		mCurrent = mClock::now();
		mElapsedTime = InSeconds(mCurrent-mLast);
        mLast = mCurrent;

		//Updating fps

		mCounter++;
		if (InSeconds(mCurrent - mLastTime) > 1.0f)
		{
			mFPS = mCounter;
			mCounter = 0;
			mLastTime = mCurrent;
		}

	}


}

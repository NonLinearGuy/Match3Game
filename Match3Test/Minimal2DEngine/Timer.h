
#ifndef INC_SHADY_ENGINE_TIMER_H
#define INC_SHADY_ENGINE_TIMER_H




//C++ headers
#include<memory>
#include<chrono>




namespace Minimal2DEngine
{

	class Timer
	{


	public:

		Timer();

		void Init();

		void Update();
	
		inline double GetDeltaTime() const {
			return mElapsedTime;
		}

		inline unsigned int GetFPS() const {
			return mFPS;
		}



	private:

		typedef std::chrono::high_resolution_clock mClock;
		typedef std::chrono::microseconds mMicroseconds;

		//for elapsed time
		mClock::time_point mLast;
		mClock::time_point mCurrent;
		double mElapsedTime;

		//For FPS
		unsigned int mFPS;
		unsigned int mCounter;
		mClock::time_point mLastTime;


		double InSeconds(mClock::duration pDuration) const;
		
	};


}


#endif

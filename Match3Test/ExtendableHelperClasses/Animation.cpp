#include "Animation.hpp"


Animation::~Animation(){
    
}


void Animation::Init(int pMaxCols, int pMaxRows, float pFrameDelay, const glm::vec2 & pFrameSize)
{
	mMaxCols=pMaxCols;
	mMaxRows=pMaxRows;
	mCurrentCol=0;
	mCurrentRow=0;
	mFrameDelay=pFrameDelay;
	mElapsed=0.0;
	mFrameSize = pFrameSize;
}



void Animation::Update(float dt)
{
    mElapsed+=dt;
	if (mElapsed > mFrameDelay) {
		if (++mCurrentCol > mMaxCols) {
			if (++mCurrentRow > mMaxRows)
				mCurrentRow = 0;

			mCurrentCol = 0;
		}
	}
}

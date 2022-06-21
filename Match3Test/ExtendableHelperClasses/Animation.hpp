#ifndef INC_ANIMATION_H
#define INC_ANIMATION_H


#include<glm/glm.hpp>


class Animation
{

protected:

	int mMaxCols;
	int mMaxRows;
	int mCurrentCol;
	int mCurrentRow;

	float mFrameDelay;
	float mElapsed;

	glm::vec2 mFrameSize;


public:

    Animation()=default;
    
	void Init(
		int pMaxCols,
		int pMaxRows,
		float pFrameDelay,
		const glm::vec2& pFrameSize
	);
    
    virtual ~Animation();

	void Update(float dt);

};

#endif

//Declaration headers
#include"GameEntity.hpp"
#include<Minimal2DEngine/SpriteRenderer.h>
#include<Minimal2DEngine/smath/Math.h>

using namespace Minimal2DEngine;

int GameEntity::sEntityCounter = 0;


const TweenData& TweenData::operator=(const TweenData& other)
{
    this->type = other.type;
    this->start = other.start;
    this->end = other.end;
    this->time = other.time;
    this->finishCallback = other.finishCallback;
    this->elapsed = 0.0;
    return *this;
}

GameEntity::GameEntity(){
    mID = sEntityCounter;
    sEntityCounter++;
    mTweening = false;
    mActive = false;
}

void GameEntity::Init(std::shared_ptr<SpriteRenderer> pRenderer,
                       std::shared_ptr<Minimal2DEngine::Texture2D> pSprite,
                       const glm::vec2& pos = glm::vec2(),const glm::vec2 pSize = glm::vec2(50,50))
{
    mRenderer = pRenderer;
    mSprite = pSprite;
    mPosition = pos;
    mSize = pSize;
    mCenter = (pos + (0.5f*pSize));
    
}



GameEntity::~GameEntity()
{

}


void GameEntity::SetPosition(const glm::vec2& pPosition)
{
	mPosition = pPosition;
    mCenter = mPosition+(.5f*mSize);
}


void GameEntity::AddTween(const glm::vec2 &toPosition, float time, ETweenType type,
                         TweenFinishCallback finishCallback){
    glm::vec2 t = toPosition -( 0.5f * glm::vec2(Globals::GEM_WIDTH,Globals::GEM_HEIGHT) );
    
    TweenData tweenData;
    tweenData.end = t;
    tweenData.start = mPosition;
    tweenData.time = time;
    tweenData.type = type;
    tweenData.elapsed = 0.0;
    tweenData.finishCallback = finishCallback;
    
    if(mTweening)
        mTweenDeq.push_back(tweenData);
    else{
        mTweening = true;
        mCurrentTween = tweenData;
    }
}




void GameEntity::Tick(float dt)
{
    if(mTweening){
        mCurrentTween.elapsed += dt;
        float v = mCurrentTween.elapsed/mCurrentTween.time;
        glm::vec2 newPos = glm::mix(mCurrentTween.start, mCurrentTween.end, v);
        SetPosition(newPos);
        mTweening = !(mCurrentTween.elapsed >= mCurrentTween.time);
        if(!mTweening){
            SetPosition(mCurrentTween.end);
            if(mCurrentTween.finishCallback != nullptr){
                mCurrentTween.finishCallback(this);
            }
            
            if(!mTweenDeq.empty()){
                mCurrentTween = mTweenDeq.front();
                mTweenDeq.pop_front();
                mTweening = true;
                mCurrentTween.elapsed = 0.0;
                mCurrentTween.start = GetPosition();
            }
           
        }
    }
}

void GameEntity::Render()
{
    mRenderer->DrawImage(mSprite, mPosition, mSize, mRotationInDegrees);
}



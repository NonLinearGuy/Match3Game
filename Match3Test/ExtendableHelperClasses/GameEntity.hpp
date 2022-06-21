#ifndef INC_GAME_ENTITY_H
#define INC_GAME_ENTITY_H

#include<memory>
#include<glm/glm.hpp>
#include"Globals.hpp"
#include <functional>
#include <deque>


namespace Minimal2DEngine{
    class SpriteRenderer;
    class Texture2D;
}

enum class ETweenType{
    LINEAR
};

class GameEntity;

using TweenFinishCallback = std::function<void(const GameEntity*const)>;

class TweenData{
    
public:
    float elapsed;
    float time;
    ETweenType type;
    glm::vec2 end;
    glm::vec2 start;
    TweenFinishCallback finishCallback;
    
    const TweenData& operator=(const TweenData& other);
    
};

class GameEntity
{

private:
    static int sEntityCounter;
    float mRadius; //for collision checks
    
    //for pooling
    int mID;
    bool mActive;
    
    //for instanced rendering
    int mTexIndex;
    
    std::deque<TweenData> mTweenDeq;
    TweenData mCurrentTween;
    bool mTweening;
    
protected:
    std::shared_ptr<Minimal2DEngine::SpriteRenderer> mRenderer;
    std::shared_ptr<Minimal2DEngine::Texture2D> mSprite;
	glm::vec2 mPosition;
	glm::vec2 mSize;
	glm::vec2 mCenter;
    float mRotationInDegrees;
    
public:

    GameEntity();
    
    void Init(std::shared_ptr<Minimal2DEngine::SpriteRenderer> pRenderer,
               std::shared_ptr<Minimal2DEngine::Texture2D> pSprite,
               const glm::vec2& pos,const glm::vec2 pSize);

    virtual ~GameEntity();
    
    //inheriters required to implement this method for pooling
    virtual void Reset() {}
    
    
    inline int GetID() const {
        return mID;
    }
    inline bool IsActive() const{
        return mActive;
    }
    
    inline bool GetRadius() const{
        return mRadius;
    }
    
    inline bool IsTweening() const {
        return mTweening;
    }


	inline glm::vec2 GetPosition() const
	{
		return mPosition;
	}

	inline glm::vec2 GetSize() const
	{
		return mSize;
	}

	inline glm::vec2 GetCenter() const
	{
		return mCenter;
	}
    
    std::shared_ptr<Minimal2DEngine::Texture2D> GetTexture() const
    {
        return mSprite;
    }
    
    int GetTexIndex() const {
        return mTexIndex;
    }
    
    void SetTexIndex(int index){
        mTexIndex = index;
    }

    void SetActive(bool active){
        mTweening = false;
        mTweenDeq.clear();
        mActive = active;
    }


    void SetPosition(const glm::vec2& newPosition);
    void SetRotation(float inDegrees){
        mRotationInDegrees = inDegrees;
    }

    inline bool IsInsideCircle(const glm::vec2& otherC,float radius){
        glm::vec2 temp = mCenter - otherC;
        float sqrD = dot(temp, temp);
        return sqrD < radius * radius;
    }

    
    void AddTween(const glm::vec2& toPosition,float time,ETweenType type,TweenFinishCallback finishCallback = nullptr);
    
    //general functions
	virtual void Tick(float dt);

	virtual void Render();


};




#endif

#include "SpriteSheetEntity.hpp"

#include<Minimal2DEngine/Texture2D.h>
#include<Minimal2DEngine/Shader.h>
#include<Minimal2DEngine/SpriteRenderer.h>

SpriteSheetEntity::SpriteSheetEntity()
{
    
}

void SpriteSheetEntity::Init(
	glm::vec2 pPosition,
	glm::vec2 pSize,
	std::shared_ptr<Minimal2DEngine::Texture2D> pSprite,
	std::shared_ptr<Minimal2DEngine::SpriteRenderer> pRenderer,
    int oRows,
    int oCols,
	int pRows,
	int pCols,
	float pFrameDelay
)
{
    GameEntity::Init(pRenderer,pSprite,pPosition,pSize),
    Animation::Init(pCols,pRows,pFrameDelay,glm::vec2(
    (pSprite->get_size().x/(pCols+1)),
    (pSprite->get_size().y / (pRows+1))));
    
    float width = pSprite->get_size().x / oCols;
    float height = pSprite->get_size().y / oRows;
    mSlicedSize.x = width * pCols;
    mSlicedSize.y = height * pRows;
}

SpriteSheetEntity::~SpriteSheetEntity()
{
}

void SpriteSheetEntity::Update(float dt)
{
	Animation::Update(dt);
}

void SpriteSheetEntity::Render()
{
	mRenderer->DrawImageRegion(
		mSprite,
		glm::vec2(mCurrentCol, mCurrentRow)*mFrameSize,
		mFrameSize,
		mPosition,
		mSize,
                               mSlicedSize
	);
}

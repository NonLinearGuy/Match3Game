#ifndef INC_SPRITE_SHEET_ENTITY_H
#define INC_SPRITE_SHEET_ENTITY_H

#include"GameEntity.hpp"
#include"Animation.hpp"
#include<glm/glm.hpp>


class SpriteSheetEntity : public GameEntity, public Animation
{
private:
    glm::vec2 mSlicedSize;
public:
    
    SpriteSheetEntity();

	void Init(
		glm::vec2 pPosition,
		glm::vec2 pSize,
		std::shared_ptr<Minimal2DEngine::Texture2D> pSprite,
		std::shared_ptr<Minimal2DEngine::SpriteRenderer> pRenderer,
        int oRows,
        int oCols,
		int tRows,
		int tCols,
		float pFrameDelay
	);

	~SpriteSheetEntity();

	bool IsDone() const
	{
		return ((mCurrentCol == mMaxCols) && (mCurrentRow == mMaxRows));
	}

    void Reset()override{
        
    }
    
	void Update(float dt);

	void Render() override;
};

#endif

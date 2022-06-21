//
//  GridController.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 01/05/22.
//

#ifndef GridController_hpp
#define GridController_hpp

#include<memory>
#include <vector>
#include <glm/glm.hpp>
#include "EntityPool.hpp"
#include "SharedEnumsAndTypes.hpp"



namespace Minimal2DEngine{
    class SpriteRenderer;
    class Texture2D;
    class TextRenderer;
}

class GemEntity;
class SpriteSheetEntity;

enum ETexIndex{
    GEM_TYPE_0,
    GEM_TYPE_1,
    GEM_TYPE_2,
    GEM_TYPE_3,
    GEM_TYPE_4,
    SLOT,
    BLOCK,
    BURST,
    SELECTION,
    HINT
};


using SharedGem = std::shared_ptr<GemEntity>;
using SharedSlot = std::shared_ptr<GemSlot>;
using SharedEffect = std::shared_ptr<SpriteSheetEntity>;

//typedefs

class GameEntitiesRenderer;
class EntityInstancingData;


class GridController{
    
    public:
    
    GridController(std::shared_ptr<Minimal2DEngine::SpriteRenderer> pRenderer,std::shared_ptr<Minimal2DEngine::TextRenderer> pTextRenderer);
    ~GridController();
    
    void SwitchState(EGameState newState);
    void OnMousePress(const glm::vec2& pos);
    void OnMouseRelease(const glm::vec2& pos);
    void Update(float deltaTime);
    void Render();
  
    //Helpers for IStates
    
    
    const std::vector<SharedSlot>& GetSlots(){
        return mGridSlots;
    }
    
    const std::vector<SharedGem>& GetGems(){
        return mGems;
    }
    
 
    SharedGem& CreateOrphanGem(bool includeInContainer = false);
   
    void CreateBurstEffect(const glm::vec2& pos);
    
    bool AreEffectsActive(){
        return !mBurstEffects.empty();
    }
    
    bool AreGemsAnimating();
    
    void SlotSelected(SharedSlot& slot);
    
    void SlotDeselected(SharedSlot& slot);
    
    void ShowHintForSlots(const SharedSlot& slot0,const SharedSlot& slot1);
    void HideHint(){
        mShowingHint = false;
    }
    
    SharedGem GetGemForSlot(const SharedSlot& slot) const;
    
    private :
    
    void SetupInstancedRenderer();
    void SetupSlots();
    
    
    glm::vec2 mPosition;
    int mSpacingX,mSpacingY;
    int mRows,mCols;
    std::vector<std::shared_ptr<GemSlot>> mGridSlots;
    std::shared_ptr<Minimal2DEngine::SpriteRenderer> mSpriteRenderer;
    std::shared_ptr<Minimal2DEngine::TextRenderer> mTextRenderer;
    
    //We will avoid using mSpriteRenderer above for Slots and Gems. Rendering them one by one will kill FPS.This will render all slots and gems in a single draw call. Significantly improving FPS. without this you will see reduction of 40-50% in FPS with mSpriteRenderer.
    std::shared_ptr<GameEntitiesRenderer> mInstancedRenderer;
    //Data for instancing needs to be prepared upfront and fed to the GPU on the fly before draw call.
    EntityInstancingData* mInstancingData;
    
    
    std::shared_ptr<GameEntity> mHintEntity;
    float mHintTextureAngle;
    bool mShowingHint;
    std::vector<std::shared_ptr<Minimal2DEngine::Texture2D>> mTextures;
    
    
    std::shared_ptr<EntityPool<GemEntity>> mGemsPool;
    //won't be shared with others
    std::shared_ptr<EntityPool<SpriteSheetEntity>> mBurstEffectPool;
    
    std::vector<SharedGem> mGems;
    std::vector<SharedEffect> mBurstEffects;
    
    
};

#endif /* GridController_hpp */

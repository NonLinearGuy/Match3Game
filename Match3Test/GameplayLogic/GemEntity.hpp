//
//  GemEntity.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 01/05/22.
//

#ifndef GemEntity_hpp
#define GemEntity_hpp

#include <stdio.h>
#include "GameEntity.hpp"
#include "SharedEnumsAndTypes.hpp"


struct CurrentSlotData{
    int row;
    int col;
    int index;
};

class GemEntity : public GameEntity{
private :
    CurrentSlotData mCurrentSlotData;
    EGemType mType;
    bool mVisible;
public:
    GemEntity();
    void Init(EGemType pType,std::shared_ptr<Minimal2DEngine::SpriteRenderer> pRenderer,
               std::shared_ptr<Minimal2DEngine::Texture2D> pSprite,
              const glm::vec2& pos,const glm::vec2 pSize);
    ~GemEntity()override;
    void Reset() override;
    void ChangePos(int pRow, int pCol);
    
    CurrentSlotData GetSlotData() const{
        return mCurrentSlotData;
    }
    void SetVisible(bool visible){
        mVisible = visible;
    }
    bool GetVisible(){
        return mVisible;
    }
    EGemType GetType(){
        return mType;
    }  
};

#endif /* GemEntity_hpp */

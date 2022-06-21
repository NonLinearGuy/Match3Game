//
//  GemEntity.cpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 01/05/22.
//

#include "GemEntity.hpp"
#include <Minimal2DEngine/random.h>
#include "../ExtendableHelperClasses/GameEntity.hpp"

using namespace Minimal2DEngine;

void GemEntity::Init(EGemType pType,std::shared_ptr<Minimal2DEngine::SpriteRenderer> pRenderer,
           std::shared_ptr<Minimal2DEngine::Texture2D> pSprite,
           const glm::vec2& pos,const glm::vec2 pSize)
{
    GameEntity::Init(pRenderer,pSprite,pos,pSize);
    mType = pType;
    mVisible = true;
}

GemEntity::GemEntity(){
    
}

GemEntity::~GemEntity(){
    
}

void GemEntity::Reset(){
    
}

void GemEntity::ChangePos(int pRow, int pCol){
    mCurrentSlotData.row = pRow;
    mCurrentSlotData.col = pCol;
    mCurrentSlotData.index = pRow * Globals::GRID_COLS + pCol;
}

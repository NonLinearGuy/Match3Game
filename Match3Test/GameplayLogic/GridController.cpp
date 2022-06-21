    //
    //  GridController.cpp
    //  Match3Test
    //
    //  Created by Ankit Singh Kushwah on 01/05/22.
    //

#include "GridController.hpp"
#include <Minimal2DEngine/SpriteRenderer.h>
#include <Minimal2DEngine/TextRenderer.h>
#include <Minimal2DEngine/Texture2D.h>
#include <Minimal2DEngine/AssetManager.h>
#include <Minimal2DEngine/random.h>
#include "GemEntity.hpp"
#include "../ExtendableHelperClasses/SpriteSheetEntity.hpp"
#include "Globals.hpp"
#include "GameEntitiesRenderer.hpp"
#include "../ExtendableHelperClasses/GameEntity.hpp"

#include <stdio.h>
#include <memory>

using namespace Minimal2DEngine;

GridController::GridController(std::shared_ptr<SpriteRenderer> pRenderer,std::shared_ptr<TextRenderer> pTextRenderer)
:mSpriteRenderer(pRenderer),mTextRenderer(pTextRenderer), mRows(Globals::GRID_ROWS ),mCols(Globals::GRID_COLS),mSpacingX(0),mSpacingY(0),mHintTextureAngle(0.0f),mShowingHint(false)
{
    
    
    
        //ORDER SHOULDN'T BE CHANGED FOR PUSHING BACK TEXTURES. LOOK ETexIndex in headers
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("gem1")); //0
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("gem2")); //1
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("gem3")); //2
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("gem4")); //3
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("gem5")); //4
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("slot")); //5
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("block")); //6
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("burst")); //7
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("selection"));//8
    mTextures.push_back(AssetManager::GetInstance()->GetTexture("hint"));//8
    
   
    
    SetupSlots();
    SetupInstancedRenderer();
    
    mGemsPool = std::make_shared<EntityPool<GemEntity>>(200);
    mBurstEffectPool = std::make_shared<EntityPool<SpriteSheetEntity>>(50);
    
    mHintEntity = std::make_shared<GameEntity>();
    mHintEntity->Init(mSpriteRenderer, mTextures[ETexIndex::HINT], glm::vec2(0.0), glm::vec2((Globals::SLOT_WIDTH * 2) + 30,Globals::SLOT_HEIGHT + 30));
    
}


GridController::~GridController()
{
    delete mInstancingData;
}

void GridController::SetupSlots()
{
    char boardPattern[64];
    std::copy(Globals::boards88[0], Globals::boards88[0] + 64, boardPattern);
    
    float boardSizeX = ((mCols - 2) * mSpacingX) + Globals::SLOT_WIDTH * mCols;
    float boardSizeY = ((mRows - 2) * mSpacingY) + Globals::SLOT_HEIGHT * mRows;
    this->mPosition.x = (Globals::WIDTH / 2.0f) - (boardSizeX/2.0);
    this->mPosition.y = (Globals::HEIGHT / 2.0f) - (boardSizeY/2.0);
    
    for(int row = 0 ; row < mRows ; ++row){
        for(int col = 0 ; col < mCols ; ++col){
            
            float x = 0.0;
            float y = 0.0;
            
            x =( mPosition.x + (col * Globals::SLOT_WIDTH) ) + mSpacingX;
            y = mPosition.y + ( mSpacingY + (row * Globals::SLOT_HEIGHT));
            int index =row * Globals::GRID_COLS + col;
            std::shared_ptr<GemSlot> newGemSlot = std::make_shared<GemSlot>();
            newGemSlot->position = glm::vec2(x,y);
            bool block = boardPattern[index] == 'x';
            newGemSlot->size = false ? glm::vec2(Globals::BLOCK_WIDTH,Globals::BLOCK_HEIGHT) : glm::vec2(Globals::SLOT_WIDTH,Globals::SLOT_HEIGHT);
            newGemSlot->center = newGemSlot->position + 0.5f * newGemSlot->size;
            newGemSlot->state = block ?ESlotState::BLOCKED :  ESlotState::FREE  ;
            newGemSlot->row = row;
            newGemSlot->col = col;
            newGemSlot->index = index;
            newGemSlot->texIndex = block ? ETexIndex::BLOCK : ETexIndex::SLOT;
            mGridSlots.push_back(newGemSlot);
            
        }
    }
    
}

void GridController::SlotSelected(SharedSlot& slot)
{
    slot->texIndex = ETexIndex::SELECTION;
    mInstancingData->texIndices[slot->index] = slot->texIndex;
}

void GridController::SlotDeselected(SharedSlot& slot)
{
    slot->texIndex = ETexIndex::SLOT;
    mInstancingData->texIndices[slot->index] = slot->texIndex;
}

void GridController::ShowHintForSlots(const SharedSlot& slot0,const SharedSlot& slot1)
{
    mShowingHint = true;
    glm::vec2 pos;
    glm::vec2 size = mHintEntity->GetSize();
    
  
    if(slot0->row > slot1->row){
        mHintTextureAngle = 90.0f;
        pos = slot0->position;
        pos -= size * glm::vec2(0.27f,0.5f);
    }
    else if(slot1->row > slot0->row){
        mHintTextureAngle = 90.0f;
        pos = slot1->position;
        pos -= size * glm::vec2(0.27f,0.5f);
    }
    if(slot0->col > slot1->col){
        mHintTextureAngle = 0.0f;
        pos = slot1->position;
        pos.y -= 15;
        pos.x -= 15;
        
    }
    else if(slot1->col > slot0->col){
        mHintTextureAngle = 0.0f;
        pos = slot0->position;
        pos.y -= 15;
        pos.x -= 15;
        
    }
    
    
    mHintEntity->SetPosition(pos);
    
    mHintEntity->SetRotation(mHintTextureAngle);

}

void GridController::SetupInstancedRenderer()
{
    mInstancingData = new EntityInstancingData();
        //Since number of slots are not going to change throughout the gameplay, we don't have to modify the instancing data for it
    for (auto slot : mGridSlots) {
        mInstancingData->translations.push_back(slot->position);
        mInstancingData->scales.push_back(slot->size);
        mInstancingData->texIndices.push_back(slot->texIndex);
    }
    
    
    mInstancedRenderer = std::make_shared<GameEntitiesRenderer>(mSpriteRenderer->GetProjection(),mSpriteRenderer->GetView());
}

SharedGem& GridController::CreateOrphanGem(bool includeInContainer){
    int gemIndex = random::getInstance()->integer(0, EGemType::COLOR_5);
    glm::vec2 size(Globals::GEM_WIDTH,Globals::GEM_HEIGHT);
    auto sprite = mTextures[gemIndex];
    EGemType type = static_cast<EGemType>( gemIndex );
    auto orphan = mGemsPool->CreateEntity();
    orphan->ChangePos(-1, -1);
    orphan->Init(type, mSpriteRenderer, sprite, glm::vec2(), glm::vec2(Globals::GEM_WIDTH,Globals::GEM_HEIGHT));
    orphan->SetTexIndex(gemIndex);
    if(includeInContainer)
        mGems.push_back(orphan);
    return orphan;
}

void GridController::CreateBurstEffect(const glm::vec2 &center)
{
    glm::vec2 size(Globals::SLOT_WIDTH,Globals::SLOT_HEIGHT);
    size*=2.0;
    glm::vec2 pos = center - 0.5f*size;
    auto effect = mBurstEffectPool->CreateEntity();
    effect->Init(pos, size, mTextures[7], mSpriteRenderer,4,7, 4, 7, 0.01);
    mBurstEffects.push_back(effect);
}


bool GridController::AreGemsAnimating(){
    bool moving = false;
    for (auto gem : mGems) {
        if(gem->IsTweening()){
            moving = true;
            break;
        }
    }
    return moving;
}


SharedGem GridController::GetGemForSlot(const SharedSlot& slot) const
{
    auto iter = std::find_if(mGems.begin(), mGems.end(), [&](const SharedGem& gem)->bool{
        return gem->GetSlotData().index == slot->index;
    });
    
    if(iter == mGems.end())
        return nullptr;
    else
        return *iter;
}



void GridController::OnMousePress(const glm::vec2 &pos)
{
    for (auto slot : mGridSlots) {
        
    }
}

void GridController::OnMouseRelease(const glm::vec2 &pos)
{
    
}

void GridController::Update(float deltaTime){
    
    bool removalNeeded = false;
    
    for (auto gem : mGems) {
        gem->Tick(deltaTime);
        if(!gem->IsActive())
            removalNeeded = true;
    }
    
        //remove-erase idiom to remove inactive gems. We don't destory them because same gems will be reused from EntityPool
    if(removalNeeded){
        mGems.erase(std::remove_if(mGems.begin(),mGems.end(),[&](const SharedGem gem)-> bool{
            return !gem->IsActive();
        }),mGems.end());
    }
    
    
    removalNeeded = false;
    
    for (auto effect : mBurstEffects) {
        effect->Update(deltaTime);
        if(effect->IsDone()){
            effect->SetActive(false);
            removalNeeded = true;
        }
    }
    
        //
    if(removalNeeded){
        mBurstEffects.erase(std::remove_if(mBurstEffects.begin(),mBurstEffects.end(),
                                           [&](const SharedEffect effect)-> bool{
            return !effect->IsActive();
        }),mBurstEffects.end());
    }
    
    
    
}

void GridController::Render(){
    
    
    for (auto gem : mGems) {
        if(!gem->GetVisible()) continue;;
        mInstancingData->translations.push_back(gem->GetPosition());
        mInstancingData->scales.push_back(gem->GetSize());
        mInstancingData->texIndices.push_back(gem->GetTexIndex());
    }
    
    mInstancedRenderer->Render(*mInstancingData, mTextures);
    
    for (auto effect : mBurstEffects) {
        effect->Render();
    }
    
        //dropping gems from vector. Keeping slots instancing data intact.
    mInstancingData->translations.resize(mGridSlots.size());
    mInstancingData->scales.resize(mGridSlots.size());
    mInstancingData->texIndices.resize(mGridSlots.size());
    
    if(mShowingHint)
        mHintEntity->Render();
    
        //PRINTS ROW,COL,STATE OF SLOT
//                for (auto slot : mGridSlots) {
//                    mTextRenderer->Text(slot->center - glm::vec2(20.0,0.0),7, glm::vec3(1.0,0.0,0.0), "%d,%d,%d",slot->type,slot->row,slot->col);
//                }
}



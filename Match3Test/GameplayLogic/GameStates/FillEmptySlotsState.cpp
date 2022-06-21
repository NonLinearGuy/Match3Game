    //
    //  FillEmptySlotsState.cpp
    //  Match3Test
    //
    //  Created by Ankit Singh Kushwah on 02/05/22.
    //

#include "FillEmptySlotsState.hpp"
#include "../GridController.hpp"
#include "../../Globals.hpp"
#include "../GemEntity.hpp"
#include "MouseInputState.hpp"
#include "MatchResolutionState.hpp"
#include "DelayState.hpp"
#include "../../SoundController.h"

FillEmptySlotsState::FillEmptySlotsState(std::shared_ptr<GridController> controller)
:IState(controller)
{
    mSoundInterval = 0.1;
    mSFXElapsed = 0;
}

FillEmptySlotsState::~FillEmptySlotsState()
{
    
}

EGameState FillEmptySlotsState::GetState() const
{
    return EGameState::FILLING_UP_EMPTY_SLOTS;
}

bool FillEmptySlotsState::IsDone() const
{
    return (!FoundFreeSlot()) && mAnimatingGems.empty();
}


std::shared_ptr<IState> FillEmptySlotsState::GetNextState() const
{
        // auto delayState = std::make_shared<DelayState>(mController);
    auto nextState = std::make_shared<MatchResolutionState>(mController);
        //delayState->Init(Globals::STATE_SWITCH_DELAY_TIME, nextState);
    return nextState;
}


void FillEmptySlotsState::DetermineEntrySlots(){
    int row = 0;
    for(int col = 0; col < Globals::GRID_COLS ; ++col){
        int index = row * Globals::GRID_COLS + col;
        SharedSlot slot = mSlots[index];
        if(slot->state == ESlotState::BLOCKED)
            continue;
        else{
            if(slot->state == ESlotState::FREE)
                mEntrySlots.push_back(slot);
        }
    }
}

SharedSlot FillEmptySlotsState::GetSlotToMoveTo(SharedGem& gem)
{
    CurrentSlotData d = gem->GetSlotData();
    int row = d.row;
    int _col = d.col;
    
    auto slot = mSlots[d.index];
    
        //slot below
    
    SharedSlot nextSlot = nullptr;
    
    if(row < Globals::GRID_ROWS - 1 && mSlots[Globals::GetIndex(row + 1, _col)]->state == ESlotState::FREE ){
        nextSlot = mSlots[Globals::GetIndex(row + 1, _col)];
    }
    else if(_col > 0 && row < Globals::GRID_ROWS-1 && mSlots[Globals::GetIndex(row, _col - 1)]->state == ESlotState::BLOCKED &&
            mSlots[Globals::GetIndex(row + 1, _col - 1)]->state == ESlotState::FREE){
        nextSlot = mSlots[Globals::GetIndex(row + 1,_col - 1)];
    }
    else if(_col < Globals::GRID_COLS - 1 && row < Globals::GRID_ROWS-1 &&  mSlots[Globals::GetIndex(row, _col + 1)]->state == ESlotState::BLOCKED &&
            mSlots[Globals::GetIndex(row + 1, _col + 1)]->state == ESlotState::FREE){
        nextSlot = mSlots[Globals::GetIndex(row + 1, _col + 1)];
    }
    
    return nextSlot;
}

void FillEmptySlotsState::PushHangingGemsDown()
{
    for(int col = 0; col < Globals::GRID_COLS ; ++col){
        for(int row = Globals::GRID_ROWS - 2; row >= 0 ; --row){
            int index = Globals::GetIndex(row, col);
            const SharedSlot& slot = mSlots[index];
            
            if(slot->state == ESlotState::BLOCKED)
                continue;
            
            
            if(slot->state == ESlotState::OCCUPIED){
                
                auto gem = mController->GetGemForSlot(slot);
                SharedSlot nextSlot = GetSlotToMoveTo(gem);
                if(nextSlot != nullptr){
                    slot->state = ESlotState::FREE;
                    gem->ChangePos(nextSlot->row, nextSlot->col);
                    gem->AddTween(nextSlot->center, Globals::GEM_FALL_ANIM_TIME,ETweenType::LINEAR);
                    mAnimatingGems.push_back(gem);
                }
                
            }
        }
    }
}

void FillEmptySlotsState::Execute()
{
        //        for (auto slot: mSlots) {
        //            if(slot->state == ESlotState::FREE){
        //                auto gem = mController->CreateNewGem(slot);
        //            }
        //        }
        //    return;
    PushHangingGemsDown();
    
    DetermineEntrySlots();
    
    for (auto entrySlot : mEntrySlots) {
        SpawnGemToFillSlot(entrySlot);
    }
    
    
}

bool FillEmptySlotsState::OnTweenFinished(SharedGem &gem){
    
    CurrentSlotData d = gem->GetSlotData();
    
    int row = d.row;
    int _col = d.col;
    
    auto slot = mSlots[d.index];
    auto nextSlot = GetSlotToMoveTo(gem);
    
    if(nextSlot != nullptr){
        slot->state = ESlotState::FREE;
        gem->ChangePos(nextSlot->row, nextSlot->col);
        gem->AddTween(nextSlot->center, Globals::GEM_FALL_ANIM_TIME,ETweenType::LINEAR);
        
        auto iter =std::find_if(mEntrySlots.begin(), mEntrySlots.end(), [&](const SharedSlot& other)->bool{
            return other->index == slot->index;
        });
        if( iter != mEntrySlots.end()){
            mSpawnedGems.push_back(SpawnGemToFillSlot(slot,true));
        }
        
        return false;
    }
    else{
        slot->type = gem->GetType();
        slot->state = ESlotState::OCCUPIED;
        mRemovedGems.push_back(gem);
        if(mSFXElapsed > mSoundInterval){
            SoundController::GetInstance()->PlayGemSettle(1.0);
            mSFXElapsed = 0.0;
        }
        
        return true;
    }
    
}


SharedGem FillEmptySlotsState::SpawnGemToFillSlot(SharedSlot &slot,bool returnAsSpawned){
    auto gem = mController->CreateOrphanGem(true);
    glm::vec2 pos = slot->center - 0.5f*gem->GetSize() - glm::vec2(0,100);
    gem->SetPosition(pos);
    gem->ChangePos(slot->row, slot->col);
    gem->AddTween(slot->center, Globals::GEM_FALL_ANIM_TIME, ETweenType::LINEAR);
    if(!returnAsSpawned)
        mAnimatingGems.push_back(gem);
    return gem;
}

void FillEmptySlotsState::Update(float dt)
{
    mSFXElapsed+=dt;
    
    for (auto gem : mAnimatingGems) {
        if(!gem->IsTweening()){
            OnTweenFinished(gem);
        }
    }
    
    for(auto gem : mRemovedGems)
    {
        auto iter = std::find_if(mAnimatingGems.begin(), mAnimatingGems.end(), [&](const SharedGem& other)->bool{
            return other->GetSlotData().index == gem->GetSlotData().index;
        });
        assert(iter != mAnimatingGems.end());
        mAnimatingGems.erase(iter);
    }
    
    mAnimatingGems.insert(mAnimatingGems.end(), mSpawnedGems.begin(),mSpawnedGems.end());
    
    if(FoundFreeSlot() && mAnimatingGems.empty()){
        Execute();
        
    }
    
    mSpawnedGems.clear();
    
    mRemovedGems.clear();
}



bool FillEmptySlotsState::FoundFreeSlot() const
{
    bool foundFreeSlot = false;
    
    for (auto slot : mSlots) {
        if(slot->state == ESlotState::FREE){
            foundFreeSlot = true;
        }
    }
    return foundFreeSlot;
}




//
//  MatchResolutionState.cpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 02/05/22.
//

#include "MatchResolutionState.hpp"
#include "FillEmptySlotsState.hpp"
#include "MouseInputState.hpp"
#include "../../Globals.hpp"
#include "../GridController.hpp"
#include "../GemEntity.hpp"
#include <algorithm>
#include <stdio.h>
#include <map>
#include <iterator>
#include "../../SoundController.h"



MatchResolutionState::MatchResolutionState(std::shared_ptr<GridController> controller)
: IState(controller)
{
    mDirectToInputState = false;
}

EGameState MatchResolutionState::GetState()const
{
    return EGameState::RESOLVING_MATCHES;
}

bool MatchResolutionState::IsDone() const
{
    return !mController->AreEffectsActive();
}

std::shared_ptr<IState> MatchResolutionState::GetNextState() const
{
    if(mDirectToInputState)
        return std::make_shared<MouseInputState>(mController);
    else
        return std::make_shared<FillEmptySlotsState>(mController);
}


MatchResolutionState::~MatchResolutionState()
{
    
}

bool MatchResolutionState::VecHasSlot(const std::vector<SharedSlot>& vec,const SharedSlot& slot)
{
    auto iter = std::find_if(vec.begin(), vec.end(), [&](SharedSlot pSlot){
        return slot->index == pSlot->index;
    });
    return iter != vec.end();
}

void MatchResolutionState::ScanHorizontally(std::vector<SharedSlot> &matchedSlots)
{
    for(int row = 0 ; row < Globals::GRID_ROWS ; ++row)
    {
        std::vector<SharedSlot> matches;
        EGemType gemType = EGemType::COLOR_1;
        
        for(int col = 0 ; col < Globals::GRID_COLS ;++col)
        {
            int index = row * Globals::GRID_COLS + col;
            SharedSlot currSlot = mSlots[index];
            if(currSlot->state == ESlotState::BLOCKED) {
                
                if(matches.size() >= Globals::COUNT_FOR_MATCH){
                    matchedSlots.insert(matchedSlots.end(),matches.begin(),matches.end());
                }
                matches.clear();
                continue;
            }
            
            if(currSlot->type == gemType){
                matches.push_back(currSlot);
            }
            else{
                if(matches.size() >= Globals::COUNT_FOR_MATCH){
                    matchedSlots.insert(matchedSlots.end(),matches.begin(),matches.end());
                }
                matches.clear();
                gemType = currSlot->type;;
                matches.push_back(currSlot);
            }
            
        }
        
        if(matches.size() >= Globals::COUNT_FOR_MATCH){
            matchedSlots.insert(matchedSlots.end(),matches.begin(),matches.end());
        }
        
        matches.clear();
    }
}


void MatchResolutionState::ScanVertically(std::vector<SharedSlot> &matchedSlots)
{
    
    
    for(int col = 0 ; col < Globals::GRID_COLS ; ++col)
    {
        std::vector<SharedSlot> matches;
        EGemType gemType = EGemType::COLOR_1;
        
        for(int row = 0 ; row < Globals::GRID_ROWS ;++row)
        {
            int index = row * Globals::GRID_COLS + col;
            SharedSlot currSlot = mSlots[index];
            
            if(currSlot->state == ESlotState::BLOCKED){
                if(matches.size() >= Globals::COUNT_FOR_MATCH){
                    for (auto slot : matches) {
                        if((!VecHasSlot(matchedSlots, slot)))
                            matchedSlots.push_back(slot);
                    }
                }
                matches.clear();
                continue;
                
            }
            
            if(currSlot->type == gemType){
                matches.push_back(currSlot);
            }
            else{
                if(matches.size() >= Globals::COUNT_FOR_MATCH){
                    for (auto slot : matches) {
                        if((!VecHasSlot(matchedSlots, slot)))
                            matchedSlots.push_back(slot);
                    }
                }
                matches.clear();
                gemType = currSlot->type;;
                matches.push_back(currSlot);
            }
            
        }
        
        if(matches.size() >= Globals::COUNT_FOR_MATCH){
            for (auto slot : matches) {
                if((!VecHasSlot(matchedSlots, slot)))
                    matchedSlots.push_back(slot);
            }
        }
        
        matches.clear();
    }
}



void MatchResolutionState::Execute()
{
    std::vector<SharedSlot> matchedSlots;
    ScanHorizontally(matchedSlots);
    ScanVertically(matchedSlots);
    if(!matchedSlots.empty())
        RemoveGemsWithEffects(matchedSlots);
    else
        mDirectToInputState = true;
}


void MatchResolutionState::Update(float dt)
{
    
}

void MatchResolutionState::RemoveGemsWithEffects(std::vector<SharedSlot>& matchedSlots)
{
    SoundController::GetInstance()->PlayMatchSFX(1.0);
    for (auto slot : matchedSlots) {
        slot->state = ESlotState::FREE;
        mController->CreateBurstEffect(slot->center);
        SharedGem gem = mController->GetGemForSlot(slot);
        if(gem)
            gem->SetActive(false);
    }
}

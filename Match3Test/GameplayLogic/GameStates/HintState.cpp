//
//  HintState.cpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 06/05/22.
//

#include "HintState.hpp"
#include "../../Globals.hpp"
#include "../SharedEnumsAndTypes.hpp"
#include "../GridController.hpp"


HintState::HintState(std::shared_ptr<GridController> controller)
: IState(controller)
{
    mHintWaitTime = Globals::HINT_WAIT_TIME;
    mElapsed = 0.0;
    mShowingHint = false;
    printf("\n hint is created");
}

HintState::~HintState()
{
    mController->HideHint();
}

EGameState HintState::GetState() const {
    return EGameState::HINTING;
}

void HintState::Execute()
{
    
}
bool HintState::IsDone() const {
    return true;
}

std::shared_ptr<IState>HintState::GetNextState() const
{
    return nullptr;
}

bool HintState::CheckForMatch(const SharedSlot& slot)
{
    bool foundMatch = false;
    
    int matchCount = 0;
    
    auto matchCheckForRow = [&](int adjacentCellRow,const SharedSlot& slot)->bool {
            //checking for one
        bool result = false;
            if(adjacentCellRow >= 0 && adjacentCellRow < Globals::GRID_ROWS){
                int index = Globals::GetIndex(adjacentCellRow,slot->col);
                SharedSlot otherSlot = mSlots[index];
                if(otherSlot->state != ESlotState::BLOCKED && (otherSlot->type == slot->type)){
                    result = true;
                }
            }
        return result;
    };
    
    for(int rowOffset = -2 ; rowOffset <=2 ; ++rowOffset){
        
        int adjacentCellRow = rowOffset + slot->row;
        if(matchCheckForRow(adjacentCellRow,slot)){
            matchCount++;
            if(matchCount >= Globals::COUNT_FOR_MATCH){
                foundMatch = true;
                break;
            }
        }
        else
        {
            matchCount=0;
        }
        
        
    }
    
    if(!foundMatch){
        
        matchCount = 0;
        
        auto matchCheckForCol = [&](int adjacentCellCol,const SharedSlot& slot)->bool {
                //checking for one
            bool result = false;
                if(adjacentCellCol >= 0 && adjacentCellCol < Globals::GRID_COLS){
                    int index = Globals::GetIndex(slot->row,adjacentCellCol);
                    SharedSlot otherSlot = mSlots[index];
                    if(otherSlot->state != ESlotState::BLOCKED && (otherSlot->type == slot->type)){
                        result = true;
                    }
                }
            return result;
        };
        
        for(int colOffset = -2 ; colOffset <=2 ; ++colOffset){
            int adjacentCellCol = colOffset + slot->col;
            if(matchCheckForCol(adjacentCellCol,slot)){
                matchCount++;
                if(matchCount >= Globals::COUNT_FOR_MATCH){
                    foundMatch = true;
                    break;
                }
            }
            else
            {
                matchCount = 0;
            }
        }
    }
    
    return foundMatch;
}

void HintState::FindSlots()
{
    SharedSlot matchedSlot0 = nullptr;
    SharedSlot matchedSlot1 = nullptr;
    
    SharedSlot otherSlot = nullptr;
    EGemType tempType;
    
    auto SwapTypeAndCheck = [&](int row,int col,SharedSlot& slot)->bool{
        otherSlot = mSlots[Globals::GetIndex(row, col)];
        if(otherSlot->state != ESlotState::BLOCKED){
            tempType = slot->type;
            slot->type = otherSlot->type;
            otherSlot->type = tempType;
            
            if(CheckForMatch(slot) || CheckForMatch(otherSlot)){
                otherSlot->type = slot->type;
                slot->type = tempType;
                matchedSlot0 = slot;
                matchedSlot1 = otherSlot;
                return true;
            }
            
            otherSlot->type = slot->type;
            slot->type = tempType;
            
        }
        return false;
    };
    
    
    for (auto iter = mSlots.rbegin() ; iter != mSlots.rend() ; ++iter) {
        SharedSlot slot = *iter;
        
        if(slot->state == ESlotState::BLOCKED)
            continue;
        
        if(slot->row > 0){
            if(SwapTypeAndCheck(slot->row - 1, slot->col, slot)){
                break;
            }
        }
        if(slot->row < Globals::GRID_ROWS - 1){
            if(SwapTypeAndCheck(slot->row + 1, slot->col, slot)){
                break;
            }
        }
         if(slot->col > 0){
             if(SwapTypeAndCheck(slot->row, slot->col - 1, slot)){
                 break;
             }
        }
        if(slot->col < Globals::GRID_COLS - 1){
            if(SwapTypeAndCheck(slot->row, slot->col + 1, slot)){
                break;
            }
        }
    }
    
    if(matchedSlot1 && matchedSlot0){
        printf("\n slots found");
        mController->ShowHintForSlots(matchedSlot0, matchedSlot1);
    }
}


void HintState::Update(float dt)
{
    if(mShowingHint) return;
    
    mElapsed+=dt;
    if(mElapsed > mHintWaitTime){
        mShowingHint = true;
        printf("\n finding slots for hint");
        FindSlots();
    }
}

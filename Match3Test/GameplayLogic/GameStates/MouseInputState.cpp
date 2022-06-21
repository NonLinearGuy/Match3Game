//
//  MouseInputState.cpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 02/05/22.
//

#include "MouseInputState.hpp"
#include "MatchResolutionState.hpp"
#include "DelayState.hpp"
#include "HintState.hpp"

#include "../GridController.hpp"
#include <memory>

#include "../GemEntity.hpp"
#include "../../SoundController.h"
#include "../../Globals.hpp"



MouseInputState::MouseInputState(std::shared_ptr<GridController> controller)
:IState(controller)
{
    mSwapIsDone = false;
    mSwapIsInProgress = false;
    mTweenFinishCount = 0;
}

MouseInputState::~MouseInputState()
{
    
}

EGameState MouseInputState::GetState()const
{
    return EGameState::MOUSE_INPUT_STATE;
}

void MouseInputState::Execute()
{
    mHintState = std::make_shared<HintState>(mController);
}

void MouseInputState::Update(float dt)
{
    if(mHintState)
        mHintState->Update(dt);
}

bool MouseInputState::IsDone()const
{
    return !mSwapIsInProgress && mSwapIsDone && !mController->AreGemsAnimating();
}


std::shared_ptr<IState> MouseInputState::GetNextState() const
{
    auto nextState = std::make_shared<MatchResolutionState>(mController);
    return nextState;
}

bool MouseInputState::PointInsideRect(const glm::vec2& pos,const glm::vec2& size, const glm::vec2 point)
{
    return (point.x > pos.x && point.x < pos.x + size.x) &&
    (point.y > pos.y && point.y < pos.y + size.y);
}

void MouseInputState::onMouseDown(const glm::vec2 &pos) {
    
    if(mSwapIsInProgress) return;
    
    mLastCursorPos = pos;
    
    mSlots = mController->GetSlots();
   for (auto slot : mSlots) {
       if(slot->state == ESlotState::BLOCKED) continue;
        if(PointInsideRect(slot->position, slot->size, pos)){
            mSelectedSlot = slot;
            break;
        }
    }
}


bool MouseInputState::CheckForMatch(SharedSlot slot)
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
            matchCount =0;
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


void MouseInputState::SwapGems(SharedSlot one, SharedSlot two)
{
    
    SharedGem gemOne = mController->GetGemForSlot(one);
    assert(gemOne != nullptr);
    SharedGem gemTwo = mController->GetGemForSlot(two);
    assert(gemTwo != nullptr);
    
    EGemType tempType = one->type;
    
    mSwapIsInProgress = true;
    
    one->type = two->type;
    two->type = tempType;
    
    
    if(CheckForMatch(one) || CheckForMatch(two)){
        
        mSwapIsDone = true;
        
        gemOne->ChangePos(two->row, two->col);
        gemTwo->ChangePos(one->row, one->col);
        
         gemOne->AddTween(two->center, .3, ETweenType::LINEAR,std::bind(&MouseInputState::OnSwapAnimFinished,this, std::placeholders::_1));
         gemTwo->AddTween(one->center,.3,ETweenType::LINEAR,std::bind(&MouseInputState::OnSwapAnimFinished,this, std::placeholders::_1));
       
    }
    else{
        two->type = one->type;
        one->type = tempType;
        
        gemOne->AddTween(two->center, .3, ETweenType::LINEAR);
        gemTwo->AddTween(one->center,.3,ETweenType::LINEAR);
        
        gemOne->AddTween(one->center, 0.1, ETweenType::LINEAR,std::bind(&MouseInputState::OnSwapAnimFinished,this, std::placeholders::_1));
        gemTwo->AddTween(two->center, 0.1, ETweenType::LINEAR,std::bind(&MouseInputState::OnSwapAnimFinished,this, std::placeholders::_1));
    }
}


void MouseInputState::OnSwapAnimFinished(const GameEntity* const entity)
{
    const GemEntity* const gem = dynamic_cast<const GemEntity* const>(entity);
    assert(gem != nullptr);
    
    
    mTweenFinishCount++;
    if(mTweenFinishCount >= 2){
        mSwapIsInProgress = false;
        mTweenFinishCount = 0;
        SoundController::GetInstance()->PlaySwapSFX(1.0);
    }
    
    SharedSlot slot = mSlots[Globals::GetIndex(gem->GetSlotData().row, gem->GetSlotData().col)];
    
    if(slot != nullptr)
        mController->SlotDeselected(slot);
    
}

void MouseInputState::onMouseUp(const glm::vec2 &pos) {
    
    if(mSwapIsInProgress) return;
    
    bool canSwap = mSelectedSlot != nullptr;
    
    if(!canSwap) {
        printf("\n cannot swap slot %d,%d because its on edge");
        return;
    }
    
    glm::vec2 delta = pos-mLastCursorPos;
    float len = glm::length(delta);
    delta = glm::normalize(delta);
    
    int row = mSelectedSlot->row;
    int col = mSelectedSlot->col;
    
    if(len > Globals::DRAG_THRESOLD){
        if(glm::dot(delta, glm::vec2(1.0,0.0)) > 0.8f){
            col++;
        }
        else if(glm::dot(delta, glm::vec2(-1.0,0.0)) > 0.8f){
            col--;
        }
        else if(glm::dot(delta, glm::vec2(0.0,1.0)) > 0.8f){
            row++;
        }
        else if(glm::dot(delta, glm::vec2(0.0,-1.0)) > 0.8f){
            row--;
        }
        
        if(row >= Globals::GRID_ROWS || row < 0 || col >= Globals::GRID_COLS || col < 0){
            printf("can't swap. other gem is on edge");
            return;
        }
            
        
        int index = Globals::GetIndex(row, col);
        
        SharedSlot secondSlot = mSlots[index];
        if(secondSlot->state == ESlotState::BLOCKED)
            return;
        else{
            assert(secondSlot->state != ESlotState::FREE); //this shouldn't happen
//            mController->SlotSelected(mSelectedSlot);
//            mController->SlotSelected(secondSlot);
            SwapGems(mSelectedSlot, secondSlot);
        }
    }
    else{
        mController->SlotSelected(mSelectedSlot);
        mSelectedSlots.push_back(mSelectedSlot);
        if(mSelectedSlots.size() == 2){
            int rowDiff =   mSelectedSlots[0]->row - mSelectedSlots[1]->row;
            int colDiff = mSelectedSlots[0]->col - mSelectedSlots[1]->col;

            bool adjacent = (abs(rowDiff) == 0  || abs(colDiff) == 0) && abs(colDiff) < 2 && abs(rowDiff) < 2;
           if(adjacent){
            SwapGems(mSelectedSlots[0],mSelectedSlots[1]);
               mSelectedSlots.clear();
           }
           else{
               mController->SlotDeselected(mSelectedSlots[0]);
               mController->SlotDeselected(mSelectedSlots[1]);
               mSelectedSlots.clear();
           }
        }
    }
}






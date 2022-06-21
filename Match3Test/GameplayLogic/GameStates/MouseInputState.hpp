//
//  MouseInputState.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 02/05/22.
//

#ifndef MouseInputState_hpp
#define MouseInputState_hpp

#include <stdio.h>
#include "IState.hpp"
#include <glm/glm.hpp>

class GameEntity;
class HintState;

class MouseInputState : public IState
{
private:
    
    std::vector<SharedSlot> mSlots;
    std::vector<SharedGem> mGems;
    glm::vec2 mLastCursorPos;
    
public:
    MouseInputState(std::shared_ptr<GridController> controller);
    EGameState GetState() const override;
     ~MouseInputState();
    void Execute()override;
    bool IsDone() const override;
    std::shared_ptr<IState> GetNextState() const override;
    void Update(float dt)override;
    
   
    void onMouseDown(const glm::vec2& pos);
    void onMouseUp(const glm::vec2& pos);
    void OnSwapAnimFinished(const GameEntity* const entity);

private:
    
    bool PointInsideRect(const glm::vec2& pos,const glm::vec2& size, const glm::vec2 point);
    bool CheckForMatch(SharedSlot one);
    void SwapGems(SharedSlot one, SharedSlot two );
    
    //for selection swap
    std::vector<SharedSlot> mSelectedSlots;
    std::shared_ptr<HintState> mHintState;
    
    //for drag swap
    glm::vec2 mCursorStart;
    SharedSlot mSelectedSlot;
    
    bool mSwapIsDone;
    bool mSwapIsInProgress;
    int  mTweenFinishCount;
    
};


#endif /* MouseInputState_hpp */

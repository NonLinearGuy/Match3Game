//
//  MatchResolutionState.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 02/05/22.
//

#ifndef MatchResolutionState_hpp
#define MatchResolutionState_hpp

#include <stdio.h>
#include "IState.hpp"

class MatchResolutionState : public IState{
public:
    MatchResolutionState(std::shared_ptr<GridController> controller);
    EGameState GetState() const override;
    ~MatchResolutionState();
    void Execute()override;
    bool IsDone()const override;
    std::shared_ptr<IState> GetNextState()const override;
    void Update(float dt)override;
    
private:
    bool VecHasSlot(const std::vector<SharedSlot>& vec,const SharedSlot& slot);
    void ScanHorizontally(std::vector<SharedSlot>& slots);
    void ScanVertically(std::vector<SharedSlot>& slots);
    void RemoveGemsWithEffects(std::vector<SharedSlot>& matchedSlots);
    
    bool mDirectToInputState;
    
    
    
};

#endif /* MatchResolutionState_hpp */

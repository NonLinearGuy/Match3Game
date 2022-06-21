//
//  HintState.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 06/05/22.
//

#ifndef HintState_hpp
#define HintState_hpp

#include <stdio.h>
#include "IState.hpp"

class HintState : public IState
{
public:
    HintState(std::shared_ptr<GridController> controller);
    ~HintState();
    EGameState GetState() const override;
    void Execute() override;
    bool IsDone() const override;
    std::shared_ptr<IState> GetNextState() const override;
    void Update(float dt) override;
private:
    bool CheckForMatch(const SharedSlot& slot);
    void FindSlots();
    bool mShowingHint;
    float mElapsed;
    float mHintWaitTime;
};

#endif /* HintState_hpp */

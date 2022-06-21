//
//  DelayState.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 02/05/22.
//

#ifndef DelayState_hpp
#define DelayState_hpp

#include <stdio.h>
#include "IState.hpp"
#include "../SharedEnumsAndTypes.hpp"

class DelayState : public IState{
public:
    
    DelayState(std::shared_ptr<GridController> controller);
    ~DelayState();
    EGameState GetState() const override;
    void Execute() override;
    bool IsDone() const override;
    std::shared_ptr<IState> GetNextState() const override;
    void Update(float dt) override;
    void Init(float delay,std::shared_ptr<IState> nextState){
        mDelay = delay;
        mNextState = nextState;
    }

    private :
    std::shared_ptr<IState> mNextState;
    float mElapsedTime;
    float mDelay;
    
};


#endif /* DelayState_hpp */

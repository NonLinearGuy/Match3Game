//
//  DelayState.cpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 05/05/22.
//

#include"DelayState.hpp"



DelayState::DelayState(std::shared_ptr<GridController> controller)
: IState(controller),mElapsedTime(0.0f),mDelay(1.0f)
{
    
}
DelayState::~DelayState(){
    
}

EGameState DelayState::GetState() const {
    return EGameState::DELAY;
}

void DelayState::Execute() {
    
}

void DelayState::Update(float dt){
    mElapsedTime+=dt;
}


bool DelayState::IsDone() const {
    return mElapsedTime >= mDelay;
}

std::shared_ptr<IState> DelayState::GetNextState() const{
    return mNextState;
}

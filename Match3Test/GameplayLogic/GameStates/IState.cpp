//
//  IState.cpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 02/05/22.
//

#include "IState.hpp"
#include "../GridController.hpp"
#include "../GemEntity.hpp"


IState::IState(std::shared_ptr<GridController> controller)
:
mController(controller)
{
    mSlots = mController->GetSlots();
    mGems = mController->GetGems();
}

IState::~IState(){
    
}

//
//  IState.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 02/05/22.
//

#ifndef IState_hpp
#define IState_hpp

#include <stdio.h>
#include <memory>
#include <vector>
#include "../SharedEnumsAndTypes.hpp"

class GridController;
struct GemSlot;
class GemEntity;

using SharedSlot = std::shared_ptr<GemSlot>;
using SharedGem = std::shared_ptr<GemEntity>;



class IState{
    protected:
    std::shared_ptr<GridController> mController;
    std::vector<SharedSlot> mSlots;
    std::vector<SharedGem> mGems;
    
    public:
    
    IState(std::shared_ptr<GridController> controller);
    virtual EGameState GetState() const = 0;
    virtual ~IState();
    virtual void Execute() = 0;
    virtual bool IsDone() const = 0;
    virtual std::shared_ptr<IState> GetNextState() const = 0;
    virtual void Update(float dt) = 0;
    
};

#endif /* IState_hpp */

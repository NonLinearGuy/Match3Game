//
//  FillEmptySlotsState.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 02/05/22.
//

#ifndef FillEmptySlotsState_hpp
#define FillEmptySlotsState_hpp

#include "IState.hpp"
#include <map>



class FillEmptySlotsState : public IState
{
public:
    FillEmptySlotsState(std::shared_ptr<GridController> controller);
    EGameState GetState() const override;
     ~FillEmptySlotsState();
    void Execute()override;
    bool IsDone()const override;
    std::shared_ptr<IState> GetNextState() const override;
    void Update(float dt)override;
    
    
private:
    
    SharedSlot GetSlotToMoveTo(SharedGem& gem);
    void DetermineEntrySlots();
    void PushHangingGemsDown();
    SharedGem SpawnGemToFillSlot(SharedSlot& slot,bool returnAsSpawned = false);
    bool OnTweenFinished(SharedGem& gem);
    bool FoundFreeSlot() const;

    
    std::vector<SharedGem> mAnimatingGems;
    std::vector<SharedGem> mRemovedGems;
    std::vector<SharedGem> mSpawnedGems;
    std::vector<SharedSlot> mEntrySlots;
    
    float mSoundInterval;
    float mSFXElapsed;
    
};

#endif /* FillEmptySlotsState_hpp */

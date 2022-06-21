//
//  SharedEnums.h
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 01/05/22.
//

#ifndef Shared_Enums_h
#define Shared_Enums_h

#include<glm/glm.hpp>
#include<memory>

enum EGemType{
    COLOR_1,
    COLOR_2,
    COLOR_3,
    COLOR_4,
    COLOR_5,
    MAX
};

enum EGameState{
    FILLING_UP_EMPTY_SLOTS,
    MOUSE_INPUT_STATE,
    RESOLVING_MATCHES,
    DELAY,
    HINTING
};


enum ESlotState{
    BLOCKED,
    OCCUPIED,
    FREE
};

struct GemSlot{
    
    int row,col,index;
    ESlotState state;
    EGemType type;
    glm::vec2 position;
    glm::vec2 center;
    glm::vec2 size;
    int texIndex;
    
};

#endif /* Shared_Enums_h */

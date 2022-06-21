#ifndef INC_GLOBALS_HPP
#define INC_GLOBALS_HPP


//C++ Headers
#include<cstdint>
#include<glm/glm.hpp>


class Globals
{

public:

	//Compile-time constants
    static const int WIDTH;
    static const int HEIGHT;
    static const int MAX_KEYS;
    static const int GRID_ROWS;
    static const int GRID_COLS;
    static const int COUNT_FOR_MATCH;
    static const int GEM_WIDTH;
    static const int GEM_HEIGHT;
    static const int SLOT_WIDTH;
    static const int SLOT_HEIGHT;
    static const int BLOCK_WIDTH;
    static const int BLOCK_HEIGHT;
    static const int DRAG_THRESOLD;
    
    
    static const float STATE_SWITCH_DELAY_TIME;
    static const float GEM_FALL_ANIM_TIME;
    static const float HINT_WAIT_TIME;
	//Enum classes

	enum class Keys :std::int8_t { UP, DOWN, LEFT, RIGHT };
    
    static inline int GetIndex(int row,int col){
        return row * GRID_COLS + col;
    }
    
    static constexpr char boards88[3][64] = {
        {
        'x','x','o','o','o','o','x','x',
        'x','x','o','o','o','o','x','x',
        'x','o','o','o','o','o','o','x',
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        'x','o','o','x','x','o','o','x',
        'x','o','o','x','x','o','o','x',
        'x','o','o','x','x','o','o','x'
        },
        {
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        },
        {
        'x','x','o','o','o','o','x','x',
        'x','x','o','o','o','o','x','x',
        'x','o','o','o','o','o','o','x',
        'o','o','o','o','o','o','o','o',
        'o','o','o','o','o','o','o','o',
        'x','o','o','x','x','o','o','x',
        'x','o','o','x','x','o','o','x',
        'x','o','o','x','x','o','o','x'
        
        }

        };
    
   
    
   
    
    
    

};



#endif

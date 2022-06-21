//
//  EntityPool.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 01/05/22.
//

#ifndef EntityPool_hpp
#define EntityPool_hpp

#include <vector>
#include <memory>
#include "GameEntity.hpp"
#include <stdio.h>

template<typename Type>
class EntityPool{
public:
    
    EntityPool(int capacity = 100){
        static_assert(std::is_base_of<GameEntity, Type>::value, "must derive from GameEntity");
        for(int i = 0 ; i < capacity ; ++i){
            std::shared_ptr<Type> newEntity = std::make_shared<Type>();
            mPool.push_back(newEntity);
        }
    }
    
    std::shared_ptr<Type> CreateEntity(){
        auto iter = std::find_if(mPool.begin(), mPool.end(),[&](std::shared_ptr<Type> entity){
            return !entity->IsActive();
        });
        assert(iter != mPool.end());
        std::shared_ptr<Type> entity = std::static_pointer_cast<Type>((*iter));
        entity->Reset();
        entity->SetActive(true);
        return entity;
    }
    
private:
    std::vector<std::shared_ptr<Type>> mPool;
};

#endif /* EntityPool_hpp */

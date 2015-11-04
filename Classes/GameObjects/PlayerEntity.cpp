//
//  PlayerEntity.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "PlayerEntity.h"

USING_NS_CC;

bool PlayerEntity::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    return true;
}


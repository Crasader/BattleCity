//
//  Born.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "Born.h"

USING_NS_CC;

Born* Born::createBorn(){
    auto born = Born::create();
    if (born->initWithFile("star1.png")) {
        _offset = Vec2(110, 4);
    }
    return born;
}

bool Born::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    return true;
}


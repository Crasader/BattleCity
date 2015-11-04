//
//  StandardMoveComponent.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__StandardMoveComponent__
#define __BattleCity__StandardMoveComponent__

#include "cocos2d.h"

class StandardMoveComponent : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(StandardMoveComponent);
    
private:
    cocos2d::Vec2 velocity;
    void update(float delta);
};

#endif /* defined(__BattleCity__StandardMoveComponent__) */

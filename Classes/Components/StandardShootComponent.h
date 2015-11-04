//
//  StandardShootComponent.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__StandardShootComponent__
#define __BattleCity__StandardShootComponent__

#include "cocos2d.h"

class StandardShootComponent : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(StandardShootComponent);
private:
    std::string _bulletFrameName;
    float _totalTime;
    float _nextShotTime;
    void update(float delta);
};

#endif /* defined(__BattleCity__StandardShootComponent__) */

//
//  CCAnimationHelper.h
//  BattleCity
//
//  Created by Jay on 15/10/12.
//
//

#ifndef __BattleCity__CCAnimationHelper__
#define __BattleCity__CCAnimationHelper__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class AnimationHelper : public cocos2d::Animation
{
public:
    static Animation* createWithSpriteFrame(const std::string& frameName, unsigned int frameCount = 1, float delay = 0.0f);
};

#endif /* defined(__BattleCity__CCAnimationHelper__) */

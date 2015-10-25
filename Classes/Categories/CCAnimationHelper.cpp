//
//  CCAnimationHelper.cpp
//  BattleCity
//
//  Created by Jay on 15/10/12.
//
//

#include "CCAnimationHelper.h"

Animation* AnimationHelper::createWithSpriteFrame(const std::string& frameName, unsigned int frameCount/* = 1 */, float delay/* = 0.0f*/)
{
    char str[100] = {0};
    Vector<SpriteFrame*> frames(frameCount);
    for(int i = 1; i <= 2; i++) //Iterate for the number of images you have
    {
        sprintf(str, "%s%i.png", frameName.c_str(), i);
        auto frameCache = SpriteFrameCache::getInstance();
        auto frame = frameCache->getSpriteFrameByName(str);
        frames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(frames, delay);
    return animation;
}

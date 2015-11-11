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
    if (born->initWithSpriteFrameName("star1.png")) {
        
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

void Born::blast(){
    char str[100] = {0};
    Vector<SpriteFrame*> frames(20);
    for (int j = 0; j < 2; j++)
    {
        for (int i = 1; i <= 4; i++)
        {
            sprintf(str, "star%i.png", i);
            auto frameCache = SpriteFrameCache::getInstance();
            auto frame = frameCache->getSpriteFrameByName(str);
            frames.pushBack(frame);
        }
        for (int i = 4; i >= 1; i--)
        {
            sprintf(str, "star%i.png", i);
            auto frameCache = SpriteFrameCache::getInstance();
            auto frame = frameCache->getSpriteFrameByName(str);
            frames.pushBack(frame);
        }
    }
    for (int i = 1; i <= 4; i++)
    {
        sprintf(str, "star%i.png", i);
        auto frameCache = SpriteFrameCache::getInstance();
        auto frame = frameCache->getSpriteFrameByName(str);
        frames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(frames, 0.05f);
    auto animate = Animate::create(animation);
    auto call = CallFuncN::create(CC_CALLBACK_1(Born::theEnd, this));
    auto seq = Sequence::create(animate, call, NULL);
    this->runAction(seq);
}

void Born::theEnd(Ref* pSender){
    this->removeFromParentAndCleanup(true);
}

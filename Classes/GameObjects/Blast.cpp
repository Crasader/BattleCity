//
//  Blast.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "Blast.h"
#include "CCAnimationHelper.h"
#include "GameManager.h"

USING_NS_CC;

Blast* Blast::createBlast(){
    auto blast = Blast::create();
    if (blast->initWithFile("boom0.png")) {
        
    }
    return blast;
}

bool Blast::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    return true;
}

void Blast::blast(){
    auto animation = AnimationHelper::createWithSpriteFrame("boom", 3, 0.05f);
    auto animate = Animate::create(animation);
    auto call = CallFuncN::create(CC_CALLBACK_1(Blast::theEnd, this));
    auto seq = Sequence::create(animate, call, NULL);
    this->runAction(seq);
}

void Blast::boom(){
    auto animation = AnimationHelper::createWithSpriteFrame("boom", 5, 0.05f);
    auto animate = Animate::create(animation);
    auto call = CallFuncN::create(CC_CALLBACK_1(Blast::theEnd, this));
    auto seq = Sequence::create(animate, call, NULL);
    this->runAction(seq);
}

void Blast::boomAndShowScore(int type){
    auto animation = AnimationHelper::createWithSpriteFrame("boom", 5, 0.05f);
    auto animate = Animate::create(animation);
    auto delay = DelayTime::create(1.0f);
    auto call = CallFuncN::create(CC_CALLBACK_1(Blast::theEnd, this));
    auto seq = Sequence::create(animate, delay, call, NULL);
    this->runAction(seq);
    
    char name[100] = {0};
    sprintf(name, "score%i.png", type + 1);
    auto sprite = Sprite::createWithSpriteFrameName(name);
    sprite->setPosition(Vec2(12, 12));
    this->addChild(sprite);
    
    long score = (type + 1) * 100;
    GameManager::getInstance()->addScoreBy(score);
    
    switch (type) {
        case 0:
            GameManager::getInstance()->addEnemyAKilled(1);
            break;
        case 1:
            GameManager::getInstance()->addEnemyBKilled(1);
            break;
        case 2:
            GameManager::getInstance()->addEnemyCKilled(1);
            break;
        case 3:
            GameManager::getInstance()->addEnemyDKilled(1);
            break;
        default:
            break;
    }
}

void Blast::theEnd(Ref* pSender){
    this->removeFromParentAndCleanup(true);
}


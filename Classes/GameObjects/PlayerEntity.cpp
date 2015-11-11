//
//  PlayerEntity.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "PlayerEntity.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "CCAnimationHelper.h"
#include "BulletCache.h"
#include "Blast.h"
#include "GameManager.h"

USING_NS_CC;

PlayerEntity* PlayerEntity::createPlayer(){
    auto player = PlayerEntity::create();
    if (player->initWithSpriteFrameName("tank11.png")) {
        player->setFrameName("tank11");
        player->setMode(PlayerModeNormal);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("blast.wav");
    }
    return player;
}

bool PlayerEntity::init()
{
    if ( !Entity::init() )
    {
        return false;
    }
    
    return true;
}

void PlayerEntity::setRotation(float rotation){
    if (rotation != this->getRotation()) {
        auto point = this->getPosition();
        if (rotation == 90.0 || rotation == 270)
        {
            if ((int)point.y % 12 >= 6)
            {
                point.y = (int)point.y / 12 * 12 + 12;
            }
            else
            {
                point.y = (int)point.y / 12 * 12;
            }
        }
        if (rotation == 180.0 || rotation == 0)
        {
            if ((int)point.x % 12 > 6)
            {
                point.x = (int)point.x / 12 * 12 + 12;
            }
            else
            {
                point.x = (int)point.x / 12 * 12;
            }
        }
        this->setPosition(point);
    }
    
    Entity::setRotation(rotation);
}

void PlayerEntity::update(float delta){
    if (this->isVisible()) {
        auto bulletCache = GameScene::getCurrentGameScene()->getBulletCache();
        auto bbox = this->getBoundingBox();
        if (bulletCache->isEnemyBulletCollidingWithRect(bbox)) {
            // This enemy got hit ...
            if (this->getMode() == PlayerModeNormal) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("blast.wav");
                this->gotHit();
            }
        }
    }
}

void PlayerEntity::showArmor(){
    if (!armor) {
        armor = Sprite::createWithSpriteFrameName("border1.png");
        armor->setPosition(12, 12);
        this->addChild(armor);
        auto animation = AnimationHelper::createWithSpriteFrame("border", 2, 0.05f);
        auto animate = Animate::create(animation);
        auto repeat = RepeatForever::create(animate);
        armor->runAction(repeat);
    }
    armor->setVisible(true);
    this->setMode(PlayerModeUndead);
    
    DelayTime *delayAction = DelayTime::create(3.0f);
    auto call = CallFuncN::create(CC_CALLBACK_0(PlayerEntity::hideArmor, this));
    auto seq = Sequence::create(delayAction, call, NULL);
    this->runAction(seq);
}

void PlayerEntity::hideArmor(){
    armor->setVisible(false);
    this->setMode(PlayerModeNormal);
}

void PlayerEntity::gotHit(){
    auto blast = Blast::createBlast();
    blast->setPosition(this->getPosition());
    blast->boom();
    GameScene::getCurrentGameScene()->getTileMap()->addChild(blast, 2);
    
    this->setVisible(false);
    this->setPosition(Vec2(4 * 24 + 12, 12));
    this->setRotation(0);
    
    GameManager::getInstance()->setLives(GameManager::getInstance()->getLives() - 1);
    
    if (GameManager::getInstance()->getLives() > 0) {
        GameScene::getCurrentGameScene()->addStar();
    }
    else if(!GameManager::getInstance()->getOver()){
        GameScene::getCurrentGameScene()->showOver();
    }
}




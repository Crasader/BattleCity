//
//  StandardShootComponent.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "StandardShootComponent.h"
#include "Entity.h"
#include "GameScene.h"

USING_NS_CC;

bool StandardShootComponent::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    _bulletFrameName = "bullet.png";
    this->scheduleUpdate();
    return true;
}

void StandardShootComponent::update(float delta){
    _totalTime += delta;
    
    auto parent = this->getParent();
    CCASSERT(dynamic_cast<Entity *>(parent), "node is not a Entity");
    auto entity = dynamic_cast<Entity *>(parent);
    if (entity->isVisible() && !entity->getReload() && _totalTime > _nextShotTime) {
        auto gameScene = GameScene::getCurrentGameScene();
        entity->setReload(true);
        _nextShotTime = _totalTime + 1.0f;
        
    }
}


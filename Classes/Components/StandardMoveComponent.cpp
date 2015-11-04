//
//  StandardMoveComponent.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "StandardMoveComponent.h"
#include "Entity.h"

USING_NS_CC;

bool StandardMoveComponent::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    this->scheduleUpdate();
    return true;
}

void StandardMoveComponent::update(float delta){
    auto parent = this->getParent();
    if (parent->isVisible()) {
        CCASSERT(dynamic_cast<Entity *>(parent), "node is not a Entity");
        auto entity = dynamic_cast<Entity *>(parent);
        entity->setPosition(entity->getPosition() + entity->getVelocity());
    }
}
//
//  EnemyEntity.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "EnemyEntity.h"
#include "GameManager.h"
#include "StandardMoveComponent.h"
#include "StandardShootComponent.h"
#include "Blast.h"
#include "GameScene.h"

USING_NS_CC;

bool EnemyEntity::init()
{
    if ( !Entity::init() )
    {
        return false;
    }
    
    return true;
}

EnemyEntity* EnemyEntity::createWithType(EnemyType t){
    std::string frameName;
    switch (t)
    {
        case EnemyTypeA1:
            frameName = "enemyA11";
            break;
        case EnemyTypeA2:
            frameName = "enemyA21";
            break;
        case EnemyTypeB1:
            frameName = "enemyB11";
            break;
        case EnemyTypeB2:
            frameName = "enemyB21";
            break;
        case EnemyTypeC1:
            frameName = "enemyC11";
            break;
        case EnemyTypeC2:
            frameName = "enemyC21";
            break;
        case EnemyTypeD1:
            frameName = "enemyD11";
            break;
        case EnemyTypeD2:
            frameName = "enemyD21";
            break;
        case EnemyTypeD3:
            frameName = "enemyD31";
            break;
        case EnemyTypeD4:
            frameName = "enemyD41";
            break;	
        default:
            CCASSERT(true, "unhandled enemy type");
    }
    auto fullFrameName = frameName + ".png";
    auto entity = EnemyEntity::create();
    if (entity->initWithSpriteFrameName(fullFrameName)) {
        entity->_type = t;
        entity->frameName = frameName;
        
        // Create the game logic components
        entity->addChild(StandardMoveComponent::create());
        entity->addChild(StandardShootComponent::create());
        
        // enemies start invisible
        entity->setVisible(true);
    }
    
    return entity;
}

void EnemyEntity::changeDirection(){
    int randomNumber = CCRANDOM_0_1() * 4;
    switch (randomNumber) {
        case 0:
            this->setRotation(90);
            break;
        case 1:
            this->setRotation(0);
            break;
        case 2:
            this->setRotation(270);
            break;
        case 3:
            this->setRotation(180);
            break;
        default:
            break;
    }
}

void EnemyEntity::gotHit(){
    switch (_type)
    {
        case EnemyTypeA2:
            this->die();
            break;
        case EnemyTypeB2:
            this->die();
            break;
        case EnemyTypeC2:
            this->die();
            break;
        case EnemyTypeD2:
            this->die();
            break;
        case EnemyTypeD3:
            frameName = "enemyD11";
            _type = EnemyTypeD1;
            break;
        case EnemyTypeD4:
            frameName = "enemyD31";
            _type = EnemyTypeD3;
            break;	
        default:
            this->die();
            break;
    }
}

void EnemyEntity::die(){
    GameManager::getInstance()->addCurrentEnemyCountBy(-1);
    this->setVisible(false);
    auto blast = Blast::createBlast();
    blast->setPosition(this->getPosition());
    int scoreType = _type / 2;
    if (scoreType >= 4) {
        scoreType = 3;
    }
    blast->boomAndShowScore(scoreType);
    GameScene::getCurrentGameScene()->addChild(blast, 2);
}

//
//  Entity.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "Entity.h"
#include "GameScene.h"
#include "EnemyEntity.h"

USING_NS_CC;

bool Entity::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    //游戏界面偏移量
    offSet = Vec2(110, 4);
    frameChangeCount = 3;
    _speed = 1;
    bulletSpeed = 4;
    _reload = false;
    Node* node = GameScene::getCurrentGameScene()->getChildByTag(GameSceneLayerTagMap);
    CCASSERT(dynamic_cast<TMXTiledMap*>(node), "not a CCTMXTiledMap");
    tileMap = dynamic_cast<TMXTiledMap*>(node);
    objectLayer = tileMap->getLayer("ObjectLayer");
    tileMapHeightInPixels = tileMap->getMapSize().height * tileMap->getTileSize().height;
    
    return true;
}

Vec2 Entity::getPosition()
{
    auto position = Sprite::getPosition();
    return position - offSet;
}

void Entity::setPosition(cocos2d::Vec2 pos){
    if(frameChangeCount-- << 0){
        frameChangeCount = 3;
        this->changeFrame();
    }
    
    // If the current position is (still) outside the screen no adjustments should be made!
    // This allows entities to move into the screen from outside.
    bool hasCollision = false;
    if (!GameScene::getScreenRect().intersectsRect(this->boundingBox())) {
        auto screeSize = GameScene::getScreenRect().size;
        float halfWidth = this->getContentSize().width * 0.5f;
        float halfHeight = this->getContentSize().height * 0.5f;
        
        // Cap the position so the Ship's sprite stays on the screen
        if (pos.x < halfWidth)
        {
            pos.x = halfWidth;
            
            if (dynamic_cast<EnemyEntity*>(this))
            {
                EnemyEntity *entity = dynamic_cast<EnemyEntity*>(this);
//                [entity changeDirection];
            }
        }
    }
}

bool Entity::getReload(){
    return true;
}

void Entity::setReload(bool reload){
    
}

void Entity::changeFrame(){
    
}

Vec2 Entity::getVelocity(){
    return Vec2::ZERO;
}
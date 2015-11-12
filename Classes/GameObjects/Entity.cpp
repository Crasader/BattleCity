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
#include "EnemyCache.h"
#include "PlayerEntity.h"

USING_NS_CC;

bool Entity::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    if (dynamic_cast<PlayerEntity *>(this)) {
        CCLOG("PlayerEntity");
    }
    
    frameChangeCount = 3;
    speed = 1;
    bulletSpeed = 4;
    reload = false;
    Node* node = GameScene::getCurrentGameScene()->getChildByTag(GameSceneLayerTagMap);
    CCASSERT(dynamic_cast<TMXTiledMap*>(node), "not a CCTMXTiledMap");
    tileMap = dynamic_cast<TMXTiledMap*>(node);
    objectLayer = tileMap->getLayer("ObjectLayer");
    tileMapHeightInPixels = tileMap->getMapSize().height * tileMap->getTileSize().height;
    
    return true;
}

void Entity::updatePosition(cocos2d::Vec2 pos){
    if(frameChangeCount-- < 0){
        frameChangeCount = 3;
        this->changeFrame();
    }
    
    // If the current position is (still) outside the screen no adjustments should be made!
    // This allows entities to move into the screen from outside.
    bool hasCollision = false;
    
    Rect screenRect = GameScene::getScreenRect();
    Rect boundingBox = this->boundingBox();
    boundingBox.origin.x += screenRect.origin.x;
    boundingBox.origin.y += screenRect.origin.y;
    if (screenRect.intersectsRect(boundingBox)) {
        auto screenSize = GameScene::getScreenRect().size;
        float halfWidth = this->getContentSize().width * 0.5f;
        float halfHeight = this->getContentSize().height * 0.5f;
        
        // Cap the position so the Ship's sprite stays on the screen
        if (pos.x < halfWidth){
            pos.x = halfWidth;
            
            if (dynamic_cast<EnemyEntity*>(this)){
                EnemyEntity *entity = dynamic_cast<EnemyEntity*>(this);
                entity->changeDirection();
            }
        }
        else if(pos.x > (screenSize.width - halfWidth)){
            pos.x = screenSize.width - halfWidth;
            
            if (dynamic_cast<EnemyEntity*>(this)){
                EnemyEntity *entity = dynamic_cast<EnemyEntity*>(this);
                entity->changeDirection();
            }
        }
        
        if (pos.y < halfHeight){
            pos.y = halfHeight;
            
            if (dynamic_cast<EnemyEntity*>(this))
            {
                EnemyEntity *entity = dynamic_cast<EnemyEntity*>(this);
                entity->changeDirection();
            }
        }
        else if(pos.y > (screenSize.height - halfHeight)){
            pos.y = screenSize.height - halfHeight;
            
            if (dynamic_cast<EnemyEntity*>(this))
            {
                EnemyEntity *entity = dynamic_cast<EnemyEntity*>(this);
                entity->changeDirection();
            }
        }
        if(this->getRotation() == 0) {
            hasCollision = this->checkUpCollision(pos);
        }
        else if (this->getRotation() == 90) {
            hasCollision = this->checkRightCollision(pos);
        }
        else if(this->getRotation() == 180) {
            hasCollision = this->checkDownCollision(pos);
        }
        else if(this->getRotation() == 270) {
            hasCollision = this->checkLeftCollision(pos);
        }
    }

    if (!hasCollision) {
        this->setPosition(pos);
    }
    else if(dynamic_cast<EnemyEntity *>(this)){
        auto entity = dynamic_cast<EnemyEntity *>(this);
        entity->changeDirection();
    }
}

Vec2 Entity::getStartPos(){
    Vec2 point;
    if(this->getRotation() == 0) {
        point = Vec2(this->getPosition().x, this->getPosition().y + this->getContentSize().height * 0.5f);
    }
    else if (this->getRotation() == 90) {
        point = Vec2(this->getPosition().x + this->getContentSize().width * 0.5f, this->getPosition().y);
    }
    else if(this->getRotation() == 180) {
        point = Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height * 0.5f);
    }
    else if(this->getRotation() == 270) {
        point = Vec2(this->getPosition().x - this->getContentSize().width * 0.5f, this->getPosition().y);
    }
    return point;
}

//移动速度，以及方向
Vec2 Entity::getVelocity(){
    Vec2 point;
    if(this->getRotation() == 0) {
        point = Vec2(0, speed);
    }
    else if (this->getRotation() == 90) {
        point = Vec2(speed, 0);
    }
    else if(this->getRotation() == 180) {
        point = Vec2(0, -speed);
    }
    else if(this->getRotation() == 270) {
        point = Vec2(-speed, 0);
    }
    return point;
}

Vec2 Entity::getBulletVelocity(){
    Vec2 point;
    if(this->getRotation() == 0) {
        point = Vec2(0, bulletSpeed);
    }
    else if (this->getRotation() == 90) {
        point = Vec2(bulletSpeed, 0);
    }
    else if(this->getRotation() == 180) {
        point = Vec2(0, -bulletSpeed);
    }
    else if(this->getRotation() == 270) {
        point = Vec2(-bulletSpeed, 0);
    }
    return point;
}

bool Entity::checkCollision(cocos2d::Vec2 pos){
    if (dynamic_cast<PlayerEntity *>(this)) {
//        CCLOG("x=%f,y=%f",pos.x,pos.y);
    }
    if (pos.x > 0 && pos.x < 312 && pos.y > 0 && pos.y < 312) {
        Vec2 tilePos = this->tilePosFromLocation(pos, tileMap);
        int tileGID = objectLayer->getTileGIDAt(tilePos);
        if (tileGID) {
            auto value = tileMap->getPropertiesForGID(tileGID);
            CCLOG("des:%s,type=%d",value.getDescription().c_str(),value.getType());
            if (value.getType() == Value::Type::MAP) {
                auto properties = value.asValueMap();
                if (!properties.empty()) {
                    if (properties.find("isBrick") != properties.end()){
                        auto isBrickProperty = properties.at("isBrick").asBool();
                        if (isBrickProperty) {
                            return true;
                        }
                    }
                    if (properties.find("isSteel") != properties.end()){
                        auto isSteelProperty = properties.at("isSteel").asBool();
                        if (isSteelProperty) {
                            return true;
                        }
                    }
                    if (properties.find("isBoss") != properties.end()){
                        //tile 地图上，boss填充透明块，属性为isBoss
                        auto isBossProperty = properties.at("isBoss").asBool();
                        if (isBossProperty) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

bool Entity::checkUpCollision(cocos2d::Vec2 pos){
    auto point1 = pos + Vec2(6, 12);
    auto point2 = pos + Vec2(-6, 12);
    if (this->checkCollision(point1) || this->checkCollision(point2)) {
        return true;
    }
    Vec2 tankPos = pos + Vec2(0, 12);
    if (this->checkTankCollision(tankPos)) {
        return true;
    }
    return false;
}

bool Entity::checkRightCollision(cocos2d::Vec2 pos){
    auto point1 = pos + Vec2(12, 6);
    auto point2 = pos + Vec2(12, -6);
    if (this->checkCollision(point1) || this->checkCollision(point2)) {
        return true;
    }
    Vec2 tankPos = pos + Vec2(12, 0);
    if (this->checkTankCollision(tankPos)) {
        return true;
    }
    return false;
}

bool Entity::checkDownCollision(cocos2d::Vec2 pos){
    auto point1 = pos + Vec2(6, -12);
    auto point2 = pos + Vec2(-6, -12);
    if (this->checkCollision(point1) || this->checkCollision(point2)) {
        return true;
    }
    Vec2 tankPos = pos + Vec2(0, -12);
    if (this->checkTankCollision(tankPos)) {
        return true;
    }
    return false;
}

bool Entity::checkLeftCollision(cocos2d::Vec2 pos){
    auto point1 = pos + Vec2(-12, 6);
    auto point2 = pos + Vec2(-12, -6);
    if (this->checkCollision(point1) || this->checkCollision(point2)) {
        return true;
    }
    Vec2 tankPos = pos + Vec2(-12, 0);
    if (this->checkTankCollision(tankPos)) {
        return true;
    }
    return false;
}

bool Entity::checkTankCollision(cocos2d::Point pos){
    auto gameScene = GameScene::getCurrentGameScene();
    auto player = gameScene->getDefaultPlayer();
    auto enemyCache = gameScene->getEnemyCache();
    for (auto enemy : enemyCache->getBatch()->getChildren()) {
        if (enemy->isVisible() && this != enemy) {
            Vec2 point = enemy->getPosition();
            Rect rect = Rect(point.x - 12, point.y - 12, 24, 24);
            if (rect.containsPoint(pos)) {
                return true;
            }
        }
    }
    if (player->isVisible() && this != player) {
        Vec2 point = player->getPosition();
        Rect rect = Rect(point.x - 12, point.y - 12, 24, 24);
        if (rect.containsPoint(pos)) {
            return true;
        }
    }
    return false;
}

void Entity::changeFrame(){
    int length = this->getFrameName().length();
    std::string subName = this->getFrameName().substr(length - 1);
    if (!subName.compare("1")) {
        subName = "2";
    }
    else if (!subName.compare("2")) {
        subName = "1";
    }
    std::string subNamePre = this->getFrameName().substr(0, length - 1);
    std::string name = subNamePre + subName;
    this->setFrameName(name);
    
    std::string displayName = frameName + ".png";
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(displayName);
    this->setDisplayFrame(frame);
}

Vec2 Entity::tilePosFromLocation(Vec2 location, TMXTiledMap* theTileMap){
    Vec2 pos = location;
    pos.x = (int)(pos.x / theTileMap->getTileSize().width);
    pos.y = (int)((tileMapHeightInPixels - pos.y) / theTileMap->getTileSize().height);
    
    CCASSERT(pos.x >= 0 && pos.y >= 0 && pos.x < theTileMap->getMapSize().width && pos.y < theTileMap->getMapSize().height,
             "coordinates out of bounds!");
    
    return pos;
}

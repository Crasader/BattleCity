//
//  Bullet.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "PlayerEntity.h"
#include "Blast.h"
#include "GameManager.h"

USING_NS_CC;

//游戏界面偏移量
const Vec2 Bullet::_offset(110, 4);

Bullet* Bullet::createBullet(){
    auto born = Bullet::create();
    if (born->initWithSpriteFrameName("bullet.png")) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("hit.wav");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("blast.wav");
        auto node = GameScene::getCurrentGameScene()->getChildByTag(GameSceneLayerTagMap);
        CCASSERT(dynamic_cast<TMXTiledMap*>(node), "not a CCTMXTiledMap");
        tileMap = dynamic_cast<TMXTiledMap*>(node);
        objectLayer = tileMap->getLayer("ObjectLayer");
        tileMapHeightInPixels = tileMap->getMapSize().height * tileMap->getTileSize().height;
    }
    return born;
}

bool Bullet::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    return true;
}

cocos2d::Vec2 Bullet::getPosition(){
    auto position = Sprite::getPosition();
    return position - _offset;
}

void Bullet::setPosition(cocos2d::Vec2 pos){
    pos = pos + _offset;
    Sprite::setPosition(pos);
}

void Bullet::shootBullet(cocos2d::Vec2 startPosition, cocos2d::Vec2 vel, std::string frameName, bool playerBullet, Entity* sprite){
    this->setVelocity(vel);
    this->setPosition(startPosition);
    this->setVisible(true);
    this->setIsPlayerBullet(playerBullet);
    this->setScale(0.75f);
    this->setOwner(sprite);
    if (dynamic_cast<PlayerEntity*>(sprite)) {
        this->schedule(CC_SCHEDULE_SELECTOR(Bullet::checkCollisionWithBullet));
    }
    
    // change the bullet's texture by setting a different SpriteFrame to be displayed
    auto frameCache = SpriteFrameCache::getInstance();
    auto frame = frameCache->getSpriteFrameByName(frameName);
    this->setDisplayFrame(frame);
    
    this->scheduleUpdate();
}

void Bullet::update(float delta){
    this->setPosition(this->getPosition() + velocity);
    
    // When the bullet leaves the screen, make it invisible
    if (!GameScene::getScreenRect().intersectsRect(this->boundingBox())) {
        if (dynamic_cast<PlayerEntity *>(this->getOwner())) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.wav");
        }
        this->setVisible(false);
        this->getOwner()->setReload(false);
        this->stopAllActions();
        this->unscheduleAllCallbacks();
        this->blastAt(this->getPosition());
    }
    else{
        bool hasCollision = false;
        if (this->getRotation() == 0) {
            hasCollision = this->checkUpCollision(this->getPosition());
        }
        else if(this->getRotation() == 90){
            hasCollision = this->checkRightCollision(this->getPosition());
        }
        else if(this->getRotation() == 180){
            hasCollision = this->checkDownCollision(this->getPosition());
        }
        else if(this->getRotation() == 270){
            hasCollision = this->checkLeftCollision(this->getPosition());
        }
        
        if (hasCollision) {
            this->setVisible(false);
            this->getOwner()->setReload(false);
            this->stopAllActions();
            this->unscheduleAllCallbacks();
            this->blastAt(this->getPosition());
        }
    }
}

void Bullet::checkCollisionWithBullet(float delta){
    auto batch = dynamic_cast<SpriteBatchNode *>(this->getParent());
    for(auto bullet : batch->getChildren()){
        if (bullet->isVisible() && bullet != this && this->isVisible() && dynamic_cast<PlayerEntity *>(owner))
        {
            if (bullet->getBoundingBox().intersectsRect(this->getBoundingBox()))
            {
                owner->setReload(false);
                this->unscheduleAllCallbacks();
                this->unscheduleUpdate();
                this->setVisible(false);
                bullet->unscheduleAllCallbacks();
                bullet->setVisible(false);
            }
        }
    }
}

bool Bullet::checkCollision(cocos2d::Vec2 pos){
    if (pos.x>0 && pos.x<312 && pos.y>0 && pos.y<312) {
        Vec2 tilePos = this->tilePosFromLocation(pos, tileMap);
        int tileGID = objectLayer->getTileGIDAt(tilePos);
        if (tileGID != 0) {
            auto properties = tileMap->getPropertiesForGID(tileGID).asValueMap();
            if (properties.size() > 0) {
                auto isBrickProperty = properties.at("isBrick").asBool();
                if (isBrickProperty) {
                    this->setBrickFrag(tilePos);
                    return true;
                }
                auto isSteelProperty = properties.at("isSteel").asBool();
                if (isSteelProperty) {
                    if (dynamic_cast<PlayerEntity *>(owner)) {
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.wav");
                    }
                    return true;
                }
            }
        }
    }
    
    //击中Boss判定
    if (this->getBoundingBox().intersectsRect(Rect(6 * 24, 0, 24, 24))) {
        if(!GameManager::getInstance()->getOver()){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("blast.wav");
            GameScene::getCurrentGameScene()->gameOver();
            return true;
        }
    }
    
    return false;
}

bool Bullet::checkUpCollision(cocos2d::Vec2 pos){
    auto point1 = pos + Vec2(6, 3);
    auto point2 = pos + Vec2(-6, 3);
    if (this->checkCollision(point1) || this->checkCollision(point2)) {
        return true;
    }
    return false;
}

bool Bullet::checkRightCollision(cocos2d::Vec2 pos){
    auto point1 = pos + Vec2(3, 6);
    auto point2 = pos + Vec2(3, -6);
    if (this->checkCollision(point1) || this->checkCollision(point2)) {
        return true;
    }
    return false;
}

bool Bullet::checkDownCollision(cocos2d::Vec2 pos){
    auto point1 = pos + Vec2(6, -3);
    auto point2 = pos + Vec2(-6, -3);
    if (this->checkCollision(point1) || this->checkCollision(point2)) {
        return true;
    }
    return false;
}

bool Bullet::checkLeftCollision(cocos2d::Vec2 pos){
    auto point1 = pos + Vec2(-3, 6);
    auto point2 = pos + Vec2(-3, -6);
    if (this->checkCollision(point1) || this->checkCollision(point2)) {
        return true;
    }
    return false;
}

void Bullet::setBrickFrag(cocos2d::Vec2 pos){
    int index = 26 * 4 * pos.y + 4 * pos.x;
    //分为4块碎片，左上为0，右上1，左下2，右下3
    if(this->getRotation() == 0){
        if (GameScene::getCurrentGameScene()->getBricks()[index + 2] == 1 && GameScene::getCurrentGameScene()->getBricks()[index + 3] == 1) {
            if (GameScene::getCurrentGameScene()->getBricks()[index + 0] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 0] = 1;
                this->addBrickFrag(pos, 0);
            }
            if (GameScene::getCurrentGameScene()->getBricks()[index + 1] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 1] = 1;
                this->addBrickFrag(pos, 1);
            }
        }
        else{
            if (GameScene::getCurrentGameScene()->getBricks()[index + 2] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 2] = 1;
                this->addBrickFrag(pos, 2);
            }
            if (GameScene::getCurrentGameScene()->getBricks()[index + 3] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 3] = 1;
                this->addBrickFrag(pos, 3);
            }
        }
    }
    else if(this->getRotation() == 90){
        if (GameScene::getCurrentGameScene()->getBricks()[index + 0] == 1 && GameScene::getCurrentGameScene()->getBricks()[index + 2] == 1) {
            if (GameScene::getCurrentGameScene()->getBricks()[index + 1] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 1] = 1;
                this->addBrickFrag(pos, 1);
            }
            if (GameScene::getCurrentGameScene()->getBricks()[index + 3] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 3] = 1;
                this->addBrickFrag(pos, 3);
            }
        }
        else{
            if (GameScene::getCurrentGameScene()->getBricks()[index + 0] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 0] = 1;
                this->addBrickFrag(pos, 0);
            }
            if (GameScene::getCurrentGameScene()->getBricks()[index + 2] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 2] = 1;
                this->addBrickFrag(pos, 2);
            }
        }
    }
    else if(this->getRotation() == 180){
        if (GameScene::getCurrentGameScene()->getBricks()[index + 0] == 1 && GameScene::getCurrentGameScene()->getBricks()[index + 1] == 1) {
            if (GameScene::getCurrentGameScene()->getBricks()[index + 2] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 2] = 1;
                this->addBrickFrag(pos, 2);
            }
            if (GameScene::getCurrentGameScene()->getBricks()[index + 3] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 3] = 1;
                this->addBrickFrag(pos, 3);
            }
        }
        else{
            if (GameScene::getCurrentGameScene()->getBricks()[index + 0] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 0] = 1;
                this->addBrickFrag(pos, 0);
            }
            if (GameScene::getCurrentGameScene()->getBricks()[index + 1] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 1] = 1;
                this->addBrickFrag(pos, 1);
            }
        }
    }
    else if(this->getRotation() == 270){
        if (GameScene::getCurrentGameScene()->getBricks()[index + 1] == 1 && GameScene::getCurrentGameScene()->getBricks()[index + 3] == 1) {
            if (GameScene::getCurrentGameScene()->getBricks()[index + 0] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 0] = 1;
                this->addBrickFrag(pos, 0);
            }
            if (GameScene::getCurrentGameScene()->getBricks()[index + 2] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 2] = 1;
                this->addBrickFrag(pos, 2);
            }
        }
        else{
            if (GameScene::getCurrentGameScene()->getBricks()[index + 1] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 1] = 1;
                this->addBrickFrag(pos, 1);
            }
            if (GameScene::getCurrentGameScene()->getBricks()[index + 3] == 0) {
                GameScene::getCurrentGameScene()->getBricks()[index + 3] = 1;
                this->addBrickFrag(pos, 3);
            }
        }
    }
    
    bool removeBrick = true;
    for (int i = index; i < index + 4; ++i) {
        if (GameScene::getCurrentGameScene()->getBricks()[i] == 0) {
            removeBrick = false;
        }
    }
    if (removeBrick) {
        objectLayer->removeTileAt(pos);
        for (int i = 0; i < 4; ++i) {
            GameScene::getCurrentGameScene()->removeChildByTag(index + 1, true);
        }
    }
}

void Bullet::addBrickFrag(cocos2d::Vec2 pos, int index){
    //砖块左上角坐标
    Vec2 brickPointInScreen;
    brickPointInScreen.x = 12 * pos.x;
    brickPointInScreen.y = 312 - 12 * pos.y;
    //碎块坐标
    Vec2 fragPoint;
    fragPoint.x = brickPointInScreen.x + index % 2 * 6 + 3;
    fragPoint.y = brickPointInScreen.y - index / 2 * 6 - 3;
    
    auto frag = Sprite::createWithSpriteFrameName("frag.png");
    fragPoint = fragPoint + _offset;
    frag->setPosition(fragPoint);
    int tag = 26 * 4 * pos.y + 4 * pos.x + index;
    GameScene::getCurrentGameScene()->addChild(frag, 1, tag);
}

void Bullet::blastAt(cocos2d::Vec2 pos){
    auto blast = Blast::createBlast();
    blast->setPosition(pos);
    blast->blast();
    GameScene::getCurrentGameScene()->addChild(blast, 2);
}

Vec2 Bullet::tilePosFromLocation(Vec2 location, TMXTiledMap* theTileMap){
    Vec2 pos = location;
    pos.x = (int)(pos.x / theTileMap->getTileSize().width);
    pos.y = (int)((tileMapHeightInPixels - pos.y) / theTileMap->getTileSize().height);
    
    CCASSERT(pos.x >= 0 && pos.y >= 0 && pos.x < theTileMap->getMapSize().width && pos.y < theTileMap->getMapSize().height,
              "coordinates out of bounds!");
    
    return pos;
}

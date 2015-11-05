//
//  BulletCache.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "BulletCache.h"
#include "Bullet.h"
#include "PlayerEntity.h"
#include "GameScene.h"

USING_NS_CC;

bool BulletCache::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    // get any bullet image from the Texture Atlas we're using
    auto bulletFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet.png");
    // use the bullet's texture (which will be the Texture Atlas used by the game)
    batch = SpriteBatchNode::createWithTexture(bulletFrame->getTexture());
    this->addChild(batch);
    
    // Create a number of bullets up front and re-use them whenever necessary.
    for (int i = 0; i < 50; i++)
    {
        auto bullet = Bullet::createBullet();
        bullet->setVisible(false);
        batch->addChild(bullet);
    }
    
    return true;
}

void BulletCache::shootBulletFrom(cocos2d::Vec2 startPosition, cocos2d::Vec2 velocity, std::string frameName, bool isPlayerBullet, Entity * owner){
    auto bullets = batch->getChildren();
    auto node = bullets.at(nextInactiveBullet);
    CCASSERT(dynamic_cast<Bullet *>(node), "not a Bullet!");
    auto bullet = dynamic_cast<Bullet *>(node);
    if (velocity.y > 0) {
        bullet->setRotation(0);
    }
    if (velocity.y < 0) {
        bullet->setRotation(180);
    }
    if (velocity.x > 0) {
        bullet->setRotation(90);
    }
    if (velocity.x < 0) {
        bullet->setRotation(270);
    }
    bullet->shootBullet(startPosition, velocity, frameName, isPlayerBullet, owner);
    
    nextInactiveBullet++;
    if (nextInactiveBullet >= bullets.size()) {
        nextInactiveBullet = 0;
    }
}

bool BulletCache::isPlayerBulletCollidingWithRect(cocos2d::Rect rect){
    return this->isBulletCollidingWithRect(rect, true);
}

bool BulletCache::isEnemyBulletCollidingWithRect(cocos2d::Rect rect){
    return this->isBulletCollidingWithRect(rect, false);
}

bool BulletCache::isBulletCollidingWithRect(cocos2d::Rect rect, bool usePlayerBullets){
    bool isColliding = false;
    for (auto b : batch->getChildren()) {
        if (dynamic_cast<Bullet *>(b)) {
            auto bullet = dynamic_cast<Bullet *>(b);
            if (bullet->isVisible() && usePlayerBullets == bullet->getIsPlayerBullet()) {
                if (bullet->getBoundingBox().intersectsRect(rect)) {
                    isColliding = true;
                    
                    // remove the bullet
                    bullet->getOwner()->setReload(false);
                    bullet->setVisible(false);
                    bullet->unscheduleUpdate();
                    break;
                }
            }
        }
    }
    
    return isColliding;
}

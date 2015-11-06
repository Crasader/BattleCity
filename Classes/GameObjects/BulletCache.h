//
//  BulletCache.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__BulletCache__
#define __BattleCity__BulletCache__

#include "cocos2d.h"
#include "Entity.h"

class BulletCache : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(BulletCache);
    CC_SYNTHESIZE(cocos2d::SpriteBatchNode*, batch, Batch);
    
    void shootBulletFrom(cocos2d::Vec2 startPosition, cocos2d::Vec2 velocity, std::string frameName, bool isPlayerBullet, Entity * owner);
    bool isPlayerBulletCollidingWithRect(cocos2d::Rect);
    bool isEnemyBulletCollidingWithRect(cocos2d::Rect);
private:
    int nextInactiveBullet;
    bool isBulletCollidingWithRect(cocos2d::Rect rect, bool usePlayerBullets);
};

#endif /* defined(__BattleCity__BulletCache__) */

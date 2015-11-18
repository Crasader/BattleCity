//
//  Bullet.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__Bullet__
#define __BattleCity__Bullet__

#include "cocos2d.h"
#include "Entity.h"

class Bullet : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(Bullet);
    static Bullet* createBullet();
    CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);
    CC_SYNTHESIZE(bool, isPlayerBullet, IsPlayerBullet);
    CC_SYNTHESIZE(cocos2d::TMXTiledMap*, tileMap, TileMap);
    CC_SYNTHESIZE(cocos2d::TMXLayer*, objectLayer, ObjectLayer);
    CC_SYNTHESIZE(float, tileMapHeightInPixels, TileMapHeightInPixels);
    CC_SYNTHESIZE_RETAIN(Entity*, owner, Owner);
    void update(float delta);
    void shootBullet(cocos2d::Vec2 startPosition, cocos2d::Vec2 vel, std::string frameName, bool playerBullet, Entity* sprite);
private:
    void checkCollisionWithBullet(float delta);
    bool checkCollision(cocos2d::Vec2 pos);
    bool checkUpCollision(cocos2d::Vec2 pos);
    bool checkRightCollision(cocos2d::Vec2 pos);
    bool checkDownCollision(cocos2d::Vec2 pos);
    bool checkLeftCollision(cocos2d::Vec2 pos);
    void setBrickFrag(cocos2d::Vec2 pos);
    void addBrickFrag(cocos2d::Vec2 pos, int index);
    void blastAt(cocos2d::Vec2 pos);
    
    cocos2d::Vec2 tilePosFromLocation(cocos2d::Vec2 location, cocos2d::TMXTiledMap* theTileMap);
};

#endif /* defined(__BattleCity__Bullet__) */

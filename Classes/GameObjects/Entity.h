//
//  Entity.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__Entity__
#define __BattleCity__Entity__

#include "cocos2d.h"

class Entity : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(Entity);
    CC_SYNTHESIZE(int, speed, Speed);
    CC_SYNTHESIZE(int, bulletSpeed, BulletSpeed);
    CC_SYNTHESIZE(bool, reload, Reload);
    CC_SYNTHESIZE(std::string, frameName, FrameName);
    
    cocos2d::Vec2 getStartPos();
    cocos2d::Vec2 getVelocity(); //移动速度，以及方向
    cocos2d::Vec2 getBulletVelocity();
    void ajustPosition(cocos2d::Vec2 pos);
private:
    cocos2d::TMXTiledMap* tileMap;
    cocos2d::TMXLayer* objectLayer;
    float tileMapHeightInPixels;
    int frameChangeCount;
    
    bool checkCollision(cocos2d::Vec2 pos);
    bool checkUpCollision(cocos2d::Vec2 pos);
    bool checkRightCollision(cocos2d::Vec2 pos);
    bool checkDownCollision(cocos2d::Vec2 pos);
    bool checkLeftCollision(cocos2d::Vec2 pos);
    bool checkTankCollision(cocos2d::Vec2 pos);
    void changeFrame();
    
    cocos2d::Vec2 tilePosFromLocation(cocos2d::Vec2 location, cocos2d::TMXTiledMap* theTileMap);
};

#endif /* defined(__BattleCity__Entity__) */

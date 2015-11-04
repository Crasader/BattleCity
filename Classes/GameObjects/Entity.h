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
    
    std::string _frameName;
    
    std::string getFrameName();
    void setFrameName(std::string frameName);
    int getSpeed();
    void setSpeed(int speed);
    int getBulletSpeed();
    void setBulletSpeed(int speed);
    bool getReload();
    void setReload(bool reload);
    
    cocos2d::Vec2 getVelocity(); //移动速度，以及方向
    cocos2d::Vec2 getBulletVelocity();
    cocos2d::Vec2 getStartPos();
    cocos2d::Vec2 getOffSet();
    
    virtual cocos2d::Vec2 getPosition();
    virtual void setPosition(cocos2d::Vec2 pos);
private:
    cocos2d::Point offSet;
    cocos2d::TMXTiledMap* tileMap;
    cocos2d::TMXLayer* objectLayer;
    float tileMapHeightInPixels;
    int frameChangeCount;
    int bulletSpeed;
    
    
    int _speed;
    bool _reload;
    
    bool checkUpCollision(cocos2d::Point pos);
    bool checkRightCollision(cocos2d::Point pos);
    bool checkDownCollision(cocos2d::Point pos);
    bool checkLeftCollision(cocos2d::Point pos);
    bool checkTankCollision(cocos2d::Point pos);
    void changeFrame();
};

#endif /* defined(__BattleCity__Entity__) */

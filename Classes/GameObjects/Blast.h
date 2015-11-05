//
//  Blast.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__Blast__
#define __BattleCity__Blast__

#include "cocos2d.h"

class Blast : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(Blast);
    static Blast* createBlast();
    void blast();
    void boom();
    void boomAndShowScore(int type);
    cocos2d::Vec2 getPosition();
    void setPosition(cocos2d::Vec2 pos);
    
    void theEnd(Ref* pSender);
private:
    static const cocos2d::Vec2 _offset;
};

#endif /* defined(__BattleCity__Blast__) */

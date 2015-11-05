//
//  Born.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__Born__
#define __BattleCity__Born__

#include "cocos2d.h"

class Born : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(Born);
    static Born* createBorn();
    void blast();
    cocos2d::Vec2 getPosition();
    void setPosition(cocos2d::Vec2 pos);
    void theEnd(Ref* pSender);
private:
    static const cocos2d::Vec2 _offset;
};

#endif /* defined(__BattleCity__Born__) */

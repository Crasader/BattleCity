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
    void theEnd(Ref* pSender);
private:

};

#endif /* defined(__BattleCity__Born__) */

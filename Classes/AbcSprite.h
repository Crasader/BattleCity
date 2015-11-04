//
//  AbcSprite.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__AbcSprite__
#define __BattleCity__AbcSprite__

#include "cocos2d.h"

class AbcSprite : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(AbcSprite);
    
private:

};

#endif /* defined(__BattleCity__AbcSprite__) */

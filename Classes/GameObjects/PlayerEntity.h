//
//  PlayerEntity.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__PlayerEntity__
#define __BattleCity__PlayerEntity__

#include "cocos2d.h"
#include "Entity.h"

class PlayerEntity : public Entity
{
public:
    virtual bool init();
    CREATE_FUNC(PlayerEntity);
    
private:

};

#endif /* defined(__BattleCity__PlayerEntity__) */

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

typedef enum
{
    PlayerModeNormal = 0,
    PlayerModeUndead,
} PlayerMode;

typedef enum
{
    TagArmor = 5,
} ObjectTag;

class PlayerEntity : public Entity
{
public:
    virtual bool init();
    CREATE_FUNC(PlayerEntity);
    CC_SYNTHESIZE(int, mode, Mode);
    static PlayerEntity* createPlayer();
    void setRotation(float rotation);
    void gotHit();
    void showArmor();
    void update(float delta);
private:
    cocos2d::Sprite *armor;
    void hideArmor();
};

#endif /* defined(__BattleCity__PlayerEntity__) */

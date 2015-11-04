//
//  EnemyEntity.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__EnemyEntity__
#define __BattleCity__EnemyEntity__

#include "cocos2d.h"
#import "Entity.h"

typedef enum
{
    EnemyTypeA1 = 0,
    EnemyTypeA2,
    EnemyTypeB1,
    EnemyTypeB2,
    EnemyTypeC1,
    EnemyTypeC2,
    EnemyTypeD1,
    EnemyTypeD2,
    EnemyTypeD3,
    EnemyTypeD4,
    EnemyType_MAX,
} EnemyType;

class EnemyEntity : public Entity
{
public:
    virtual bool init();
    CREATE_FUNC(EnemyEntity);
    
    static EnemyEntity* createWithType(EnemyType t);
    void gotHit();
    void changeDirection();
private:
    EnemyType _type;
    EnemyEntity* initWithType(EnemyType t);
    void initSpawnFrequency();
    void die();
};

#endif /* defined(__BattleCity__EnemyEntity__) */

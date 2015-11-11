//
//  EnemyCache.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__EnemyCache__
#define __BattleCity__EnemyCache__

#include "cocos2d.h"
#include "EnemyEntity.h"

class EnemyCache : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(EnemyCache);
    CC_SYNTHESIZE(cocos2d::SpriteBatchNode*, batch, Batch);
    void addStar();
private:
    cocos2d::Vector<EnemyEntity *> enemies;
    void initEnemies();
    void initEnemySymbols();
    void spawnEnemy(cocos2d::Vec2 vec);
    void spawnFirstThreeEnemy(float delta);
    void checkForBulletCollisions();
    void continueSpawnEnemy(float delta);
    void update(float delta);
};

#endif /* defined(__BattleCity__EnemyCache__) */

//
//  GameScene.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__GameScene__
#define __BattleCity__GameScene__

#include "cocos2d.h"

class PlayerEntity;
class BulletCache;
class EnemyCache;
class Entity;

typedef enum
{
    GameSceneLayerTagMap = 1,
    GameSceneLayerTagGame,
    GameSceneLayerTagInput,
    
} GameSceneLayerTags;

typedef enum
{
    GameSceneNodeTagBullet = 10,
    GameSceneNodeTagBulletSpriteBatch,
    GameSceneNodeTagBulletCache,
    GameSceneNodeTagEnemyCache,
    GameSceneNodeTagPlayer,
    GameSceneNodeTagBoss,
    kTagLiveLabel,
    
} GameSceneNodeTags;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    CC_SYNTHESIZE(int*, bricks, Bricks);

    static GameScene* getCurrentGameScene();
    static cocos2d::Rect getScreenRect();
    Entity* getDefaultPlayer();
    EnemyCache* getEnemyCache();
    BulletCache* getBulletCache();
    
    void addStar();
    void gameOver();
    void showOver();
    void showScore();
private:
    virtual void onEnter();
    virtual void onExit();
    
    Entity* _defaultPlayer;
    EnemyCache* _enemyCache;
    BulletCache* _bulletCache;
    
    cocos2d::Label *liveLB;
    cocos2d::Vec2 offset;
};

#endif /* defined(__BattleCity__GameScene__) */

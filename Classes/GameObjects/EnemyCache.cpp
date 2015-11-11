//
//  EnemyCache.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "EnemyCache.h"
#include "EnemyEntity.h"
#include "GameScene.h"
#include "BulletCache.h"
#include "Born.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"

USING_NS_CC;

bool EnemyCache::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    srandom(NULL);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("blast.wav");
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemyA11.png");
    this->setBatch(SpriteBatchNode::createWithTexture(frame->getTexture()));
    this->addChild(batch);
    
    this->initEnemies();
    this->initEnemySymbols();
    
    DelayTime *delayAction = DelayTime::create(1.0f);
    auto call = CallFuncN::create(CC_CALLBACK_0(EnemyCache::addStar, this));
    auto seq = Sequence::create(delayAction, call, NULL);
    this->runAction(seq);
    
    this->scheduleUpdate();
    
    return true;
}

void EnemyCache::initEnemies(){
    enemies = Vector<EnemyEntity *>(20);
    for (int i = 0; i < 20; ++i) {
        int ranNum = CCRANDOM_0_1() * EnemyType_MAX;
        auto enemy = EnemyEntity::createWithType((EnemyType)(ranNum));
        enemy->setRotation(180);
        enemy->setVisible(false);
        enemies.pushBack(enemy);
    }
}

void EnemyCache::initEnemySymbols(){
    for (int i=0; i<20; i++) {
        Vec2 point;
        auto sprite = Sprite::createWithSpriteFrameName("logo2.png");
        point.x = 442 + 18 * (i % 2);
        point.y = 300 - 18 * (i / 2);
        sprite->setPosition(point);
        this->addChild(sprite, 0, 100 + i);
    }
}

void EnemyCache::spawnEnemy(Vec2 vec){
    for (auto enemy : enemies) {
        if (!enemy->isVisible()) {
            enemy->setVisible(true);
            enemy->setPosition(vec);
            batch->addChild(enemy, 0, 0);
            
            //刚开始，生产第一辆的时候计划执行函数spawFirstThressEnemy来继续生产，直到3辆。
            if(GameManager::getInstance()->getEnemyRemain() >= 19){
                this->schedule(CC_SCHEDULE_SELECTOR(EnemyCache::spawnFirstThreeEnemy), 2.0f);
            }
            
            break;
        }
    }
}

void EnemyCache::addStar(){
    int index = (20 - GameManager::getInstance()->getEnemyRemain()) % 3;
    GameManager::getInstance()->setCurrentEnemyCount(GameManager::getInstance()->getCurrentEnemyCount() + 1);
    GameManager::getInstance()->setEnemyRemain(GameManager::getInstance()->getEnemyRemain() - 1);
    Vec2 pos;
    switch (index) {
        case 2:
            pos = Vec2(12, 12 * 25);
            break;
        case 0:
            pos = Vec2(12 * 13, 12 * 25);
            break;
        case 1:
            pos = Vec2(12 * 25, 12 * 25);
            break;
        default:
            break;
    }
    
    auto born = Born::createBorn();
    born->setPosition(pos);
    born->blast();
    this->addChild(born);
    
    //移去右上角相应的坦克标志
    this->getChildByTag(100 + GameManager::getInstance()->getEnemyRemain())->removeFromParentAndCleanup(true);
    
    DelayTime *delayAction = DelayTime::create(1.0f);
    auto call = CallFuncN::create(CC_CALLBACK_0(EnemyCache::spawnEnemy, this, born->getPosition()));
    auto seq = Sequence::create(delayAction, call, NULL);
    this->runAction(seq);
}

void EnemyCache::spawnFirstThreeEnemy(float delta){
    if(GameManager::getInstance()->getCurrentEnemyCount() > 3){
        this->unschedule(CC_SCHEDULE_SELECTOR(EnemyCache::spawnFirstThreeEnemy));
        this->schedule(CC_SCHEDULE_SELECTOR(EnemyCache::continueSpawnEnemy));
    }
    else{
        this->addStar();
    }
}

void EnemyCache::checkForBulletCollisions(){
    for (auto node : batch->getChildren()) {
        if (dynamic_cast<EnemyEntity*>(node)) {
            auto enemy = dynamic_cast<EnemyEntity*>(node);
            if (enemy->isVisible()) {
                auto bulletCache = GameScene::getCurrentGameScene()->getBulletCache();
                auto bbox = enemy->getBoundingBox();
                if (bulletCache->isPlayerBulletCollidingWithRect(bbox)) {
                    // This enemy got hit ...
                    enemy->gotHit();
                    
                    if (!enemy->isVisible()) {
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("blast.wav");
                        enemies.eraseObject(enemy);
                        enemy->removeFromParentAndCleanup(true);
                    }
                    
                    if (GameManager::getInstance()->getEnemyRemain() <= 0 && GameManager::getInstance()->getCurrentEnemyCount() == 0) {
                        auto gameScene = GameScene::getCurrentGameScene();
                        DelayTime *delayAction = DelayTime::create(3.0f);
                        auto call = CallFuncN::create(CC_CALLBACK_0(GameScene::showScore, gameScene));
                        auto seq = Sequence::create(delayAction, call, NULL);
                        gameScene->runAction(seq);
                    }
                }
            }
        }
    }
}

void EnemyCache::continueSpawnEnemy(float delta){
    if (GameManager::getInstance()->getCurrentEnemyCount() <= 3 && GameManager::getInstance()->getEnemyRemain() > 0) {
        this->addStar();
    }
}

void EnemyCache::update(float delta){
    this->checkForBulletCollisions();
}

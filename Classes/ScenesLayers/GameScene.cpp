//
//  GameScene.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "GameScene.h"
#include "CCAnimationHelper.h"
#include "GameManager.h"
#include "InputLayer.h"
#include "PlayerEntity.h"
#include "BulletCache.h"
#include "EnemyCache.h"
#include "Entity.h"
#include "EnemyEntity.h"
#include "Born.h"
#include "Blast.h"
#include "MainMenuScene.h"
#include "LevelScene.h"
#include "ScoreScene.h"

USING_NS_CC;

static GameScene *_currentGameScene = NULL;
const Rect GameScene::_screenRect(110, 4, 312, 312);

GameScene* GameScene::getCurrentGameScene(){
    CCASSERT(_currentGameScene, "GameScene instance not yet initialized!");
    return _currentGameScene;
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer, 0, GameSceneLayerTagGame);
    return scene;
}

Rect GameScene::getScreenRect(){
    return _screenRect;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    _currentGameScene = this;
    
    int _bricks[2704];
    for (int i = 0; i < 2704; ++i) {
        _bricks[0] = 0;
    }
    bricks = _bricks;
    
    auto inputLayer = InputLayer::create();
    this->addChild(inputLayer, 100, GameSceneLayerTagInput);
    
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    //灰色背景
    auto backGround = LayerColor::create(Color4B(153, 153, 153, 255), screenSize.width, screenSize.height);
    this->addChild(backGround, -10);
    
    //黑色游戏背景
    auto gameRect = LayerColor::create(Color4B(0, 0, 0, 255), screenSize.height - 8, screenSize.height - 8);
    gameRect->setPosition(_screenRect.origin);
    this->addChild(gameRect, 0);
    
    //旗子
    auto flag = Sprite::createWithSpriteFrameName("flag.png");
    flag->setPosition(50, 260);
    this->addChild(flag);
    
    //IP标签
    auto IPLB = Label::createWithSystemFont("I P", "STHeitiJ-Light", 20);
    IPLB->setColor(Color3B::BLACK);
    IPLB->setPosition(50, 200);
    this->addChild(IPLB);
    
    //玩家命数
    auto liveStr = StringUtils::format("%d", GameManager::getInstance()->getLives() - 1);
    liveLB = Label::createWithSystemFont(liveStr, "STHeitiJ-Light", 15);
    liveLB->setColor(Color3B::BLACK);
    liveLB->setPosition(54, 178);
    this->addChild(liveLB, 0, kTagLiveLabel);
    
    //小坦克标志
    auto logo = Sprite::createWithSpriteFrameName("logo1.png");
    logo->setPosition(40, 180);
    this->addChild(logo);
    
    this->initLevel();
    
    return true;
}

void GameScene::onEnter()
{
    Layer::onEnter();
}

void GameScene::onExit()
{
    Layer::onExit();
}

TMXTiledMap* GameScene::getTileMap(){
    auto node = this->getChildByTag(GameSceneLayerTagMap);
    CCASSERT(dynamic_cast<TMXTiledMap *>(node), "node is not a TMXTiledMap!");
    return dynamic_cast<TMXTiledMap *>(node);
}

PlayerEntity* GameScene::getDefaultPlayer(){
    auto node = this->getTileMap()->getChildByTag(GameSceneNodeTagPlayer);
    CCASSERT(dynamic_cast<PlayerEntity *>(node), "node is not a PlayerEntity!");
    return dynamic_cast<PlayerEntity *>(node);
}

Entity* GameScene::getDefaultBoss(){
    auto node = this->getTileMap()->getChildByTag(GameSceneNodeTagBoss);
    CCASSERT(dynamic_cast<Entity *>(node), "node is not a Entity!");
    return dynamic_cast<Entity *>(node);
}

EnemyCache* GameScene::getEnemyCache(){
    auto node = this->getTileMap()->getChildByTag(GameSceneNodeTagEnemyCache);
    CCASSERT(dynamic_cast<EnemyCache *>(node), "node is not a EnemyCache!");
    return dynamic_cast<EnemyCache *>(node);
}

BulletCache* GameScene::getBulletCache(){
    auto node = this->getTileMap()->getChildByTag(GameSceneNodeTagBulletCache);
    CCASSERT(dynamic_cast<BulletCache *>(node), "node is not a BulletCache!");
    return dynamic_cast<BulletCache *>(node);
}

void GameScene::initLevel(){
    auto levelStr = StringUtils::format("%d", GameManager::getInstance()->getLevel());
    auto stageLB = Label::createWithSystemFont(levelStr, "STHeitiJ-Light", 15);
    stageLB->setColor(Color3B::BLACK);
    stageLB->setPosition(55, 240);
    this->addChild(stageLB);
    
    auto mapName = StringUtils::format("stage%d.tmx", GameManager::getInstance()->getLevel());
    auto tileMap = TMXTiledMap::create(mapName);
    this->addChild(tileMap, 1, GameSceneLayerTagMap);
    tileMap->setPosition(_screenRect.origin);
    
    //主基地标志
    auto boss = Entity::createWithSpriteFrameName("boss.png");
    boss->setPosition(6*24 + 12, 12);
    tileMap->addChild(boss, 0, GameSceneNodeTagBoss);
    
    auto enemyCache = EnemyCache::create();
    tileMap->addChild(enemyCache, 0, GameSceneNodeTagEnemyCache);
    
    auto bulletCache = BulletCache::create();
    tileMap->addChild(bulletCache, 1, GameSceneNodeTagBulletCache);
    
    auto player = PlayerEntity::createPlayer();
    player->setPosition(4 * 24 + player->getContentSize().width * 0.5, player->getContentSize().height * 0.5);
    player->setVisible(false);
    tileMap->addChild(player, -1, GameSceneNodeTagPlayer);
    
    DelayTime *delayAction = DelayTime::create(1.0f);
    auto call = CallFuncN::create(CC_CALLBACK_0(GameScene::begin, this));
    auto seq = Sequence::create(delayAction, call, NULL);
    this->runAction(seq);
}

void GameScene::begin(){
    this->addStar();
    this->scheduleUpdate();
    auto layer = this->getChildByTag(GameSceneLayerTagInput);
    layer->scheduleUpdate();
}

void GameScene::addStar(){
    auto born = Born::createBorn();
    born->setPosition(Vec2(4 * 24 + 12, 12));
    born->blast();
    this->getTileMap()->addChild(born);
    
    DelayTime *delayAction = DelayTime::create(1.1f);
    auto call = CallFuncN::create(CC_CALLBACK_0(GameScene::showPlayer, this));
    auto seq = Sequence::create(delayAction, call, NULL);
    this->runAction(seq);
}

void GameScene::showPlayer(){
    auto player = this->getDefaultPlayer();
    player->setVisible(true);
    player->showArmor();
}

void GameScene::gameOver(){
    if (!GameManager::getInstance()->getOver()) {
        GameManager::getInstance()->setOver(true);
        auto blast = Blast::createBlast();
        blast->setPosition(this->getDefaultBoss()->getPosition());
        blast->boom();
        this->getTileMap()->addChild(blast, 2);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("fail.png");
        this->getDefaultBoss()->setDisplayFrame(frame);
        this->showOver();
    }
}

void GameScene::showOver(){
    GameManager::getInstance()->setOver(true);
    auto gameOver = Sprite::createWithSpriteFrameName("gameover.png");
    gameOver->setPosition(155 + 110, 4 - gameOver->getContentSize().height);
    auto moveTo = MoveTo::create(3.0f, Vec2(155 + 110, 4 + 155));
    this->addChild(gameOver, 100);
    gameOver->runAction(moveTo);
    
    DelayTime *delayAction = DelayTime::create(5.0f);
    auto call = CallFuncN::create(CC_CALLBACK_0(GameScene::showScore, this));
    auto seq = Sequence::create(delayAction, call, NULL);
    this->runAction(seq);
}

void GameScene::showScore(){
    auto fade = TransitionFade::create(2.0f, ScoreScene::createScene(), Color3B(255, 255, 255));
    Director::getInstance()->replaceScene(fade);
}

void GameScene::update(float delta){
    auto liveStr = StringUtils::format("%d", GameManager::getInstance()->getLives() - 1);
    if (GameManager::getInstance()->getLives() - 1 >= 0) {
        liveLB->setString(liveStr);
    }
}

void GameScene::printBricks(){
    for (int i = 0; i < 2704; ++i) {
        CCLOG("%d",bricks[i]);
    }
}

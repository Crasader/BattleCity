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

USING_NS_CC;

static GameScene *_currentGameScene = NULL;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    _currentGameScene = this;
    
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    offset = Vec2(110, 4);
    screenRect = Rect(110, 4, 312, 312);
    
    
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


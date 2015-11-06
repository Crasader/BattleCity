//
//  ScoreScene.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "ScoreScene.h"
#include "CCAnimationHelper.h"
#include "GameManager.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ScoreScene::create();
    scene->addChild(layer);
    return scene;
}

bool ScoreScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    return true;
}

void ScoreScene::onEnter()
{
    Layer::onEnter();
}

void ScoreScene::onExit()
{
    Layer::onExit();
}


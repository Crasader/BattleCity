//
//  AbcScene.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "AbcScene.h"
#include "CCAnimationHelper.h"
#include "GameManager.h"

USING_NS_CC;

Scene* AbcScene::createScene()
{
    auto scene = Scene::create();
    auto layer = AbcScene::create();
    scene->addChild(layer);
    return scene;
}

bool AbcScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    return true;
}

void AbcScene::onEnter()
{
    Layer::onEnter();
}

void AbcScene::onExit()
{
    Layer::onExit();
}


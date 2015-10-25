//
//  MainMenuScene.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "MainMenuScene.h"
#include "CCAnimationHelper.h"
#include "GameManager.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
//    this->setTouchEnabled(true);
    GameManager::getInstance()->resetGame();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res_default.plist");
    
    auto background = Sprite::create("TankTitle.png");
    background->setPosition(visibleSize.width * 0.5, -background->getContentSize().height * 0.5);
    this->addChild(background, -1, kTagBackGround);
    auto act = MoveTo::create(3.0, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    auto call = CallFuncN::create(CC_CALLBACK_1(MainMenuScene::showTankIcon, this));
    auto seq = Sequence::create(act, call, NULL);
    seq->setTag(kTagMoveToCenterAction);
    background->runAction(seq);
    
    MenuItemFont::setFontName("Verdana-Bold");
    MenuItemFont::setFontSize(20);
    
    auto beginItem = CCMenuItemFont::create("开始", CC_CALLBACK_1(MainMenuScene::beginItemTouched, this));
    beginItem->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.4);
    auto optionItem = CCMenuItemFont::create("选项", CC_CALLBACK_1(MainMenuScene::optionItemTouched, this));
    optionItem->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.3);
    
    auto menu = Menu::create(beginItem, optionItem, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setTag(100);
    background->addChild(menu, 1);
    
    return true;
}

void MainMenuScene::onEnter()
{
    Layer::onEnter();
    
    // Register Touch Event
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        cocos2d::log("You touched %f, %f", touch->getLocationInView().x, touch->getLocationInView().y);
        auto target = static_cast<MainMenuScene*>(event->getCurrentTarget());
        if (target->getChildByTag(kTagBackGround)->getNumberOfRunningActions() > 0) {
            target->getChildByTag(kTagBackGround)->stopAllActions();
            Size visibleSize = Director::getInstance()->getVisibleSize();
            auto move = MoveTo::create(0.1f, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
            auto call = CallFuncN::create(CC_CALLBACK_1(MainMenuScene::showTankIcon, target));
            auto seq = Sequence::create(move, call, NULL);
            target->getChildByTag(kTagBackGround)->runAction(seq);
        }
        return true;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event) {
        cocos2d::log("touch moved");
    };
    listener->onTouchEnded = [](Touch* touch, Event* event) {
        cocos2d::log("touch ended");
    };
    listener->setSwallowTouches(true);//不向下传递触摸
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainMenuScene::onExit()
{
    // You don't need to unregister listeners here as new API
    // removes all linked listeners automatically in CCNode's destructor
    // which is the base class for all cocos2d DRAWING classes
    
    Layer::onExit();
}

void MainMenuScene::update(float dt)
{
    
}

void MainMenuScene::showTankIcon(Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::createWithSpriteFrameName("tank11.png");
    sprite->setPosition(Vec2(visibleSize.width * 0.4, visibleSize.height * 0.4));
    sprite->setRotation(90);
    this->addChild(sprite);
    auto animation = AnimationHelper::createWithSpriteFrame("tank1", 2, 0.1);
    auto animate = Animate::create(animation);
    auto repeat = RepeatForever::create(animate);
    sprite->runAction(repeat);
}

void MainMenuScene::beginItemTouched(Ref* pSender)
{
    Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

void MainMenuScene::optionItemTouched(Ref* pSender)
{
    
}

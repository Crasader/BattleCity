//
//  LevelScene.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "LevelScene.h"
#include "CCAnimationHelper.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* LevelScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    //敌人击杀数量清零
    GameManager::getInstance()->resetLevel();
    auto backLayer = LayerColor::create(Color4B(153, 153, 153, 255), screenSize.width, screenSize.height);
    this->addChild(backLayer, 0);
    
    std::string levelStr = StringUtils::format("第 %d 关", GameManager::getInstance()->getLevel());
    levelLB = Label::createWithSystemFont(levelStr, "Verdana-Bold", 20);
    levelLB->setColor(Color3B::BLACK);
    levelLB->setPosition(Vec2(screenSize.width * 0.5, screenSize.height * 0.6));
    this->addChild(levelLB);
    
    if (GameManager::getInstance()->getChooseLevel()) {
        GameManager::getInstance()->setChooseLevel(false);
        this->chooseLevel();
    }
    else{
        DelayTime *delayAction = DelayTime::create(3.0f);
        auto call = CallFuncN::create(CC_CALLBACK_1(LevelScene::gotoNextLevel, this));
        auto seq = Sequence::create(delayAction, call, NULL);
        this->runAction(seq);
    }
    
    return true;
}

void LevelScene::onEnter()
{
    Layer::onEnter();
}

void LevelScene::onExit()
{
    Layer::onExit();
}


void LevelScene::chooseLevel(){
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    MenuItemFont::setFontName("Verdana-Bold");
    MenuItemFont::setFontSize(20);
    
    auto beginItem = CCMenuItemFont::create("Go !!!", CC_CALLBACK_1(LevelScene::beginItemTouched, this));
    beginItem->setColor(Color3B::BLACK);
    beginItem->setPosition(screenSize.width * 0.5, screenSize.height * 0.3);
    
    auto menu = Menu::create(beginItem, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setTag(100);
    this->addChild(menu);
    
    auto sprite = Sprite::createWithSpriteFrameName("tank11.png");
    sprite->setPosition(Vec2(screenSize.width * 0.38, screenSize.height * 0.3));
    sprite->setRotation(90);
    this->addChild(sprite);
    auto animation = AnimationHelper::createWithSpriteFrame("tank1", 2, 0.1);
    auto animate = Animate::create(animation);
    auto repeat = RepeatForever::create(animate);
    sprite->runAction(repeat);
}

void LevelScene::beginItemTouched(Ref* pSender){
    this->gotoNextLevel(pSender);
}

void LevelScene::gotoNextLevel(Ref* pSender){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("start.wav");
    auto fade = TransitionFade::create(2.0f, GameScene::createScene(), Color3B(255, 255, 255));
    Director::getInstance()->replaceScene(fade);
}

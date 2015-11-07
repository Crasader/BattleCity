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
#include "LevelScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ScoreScene::create();
    scene->addChild(layer, 0);
    return scene;
}

bool ScoreScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    count = 0;
    Size screenSize = Director::getInstance()->getVisibleSize();
    //黑色背景
    auto backGround = LayerColor::create(Color4B(0, 0, 0, 255), screenSize.width, screenSize.height);
    this->addChild(backGround, -10);
    
    auto HIScoreLB = Label::createWithSystemFont("HI-SCORE", "ArialRoundedMTBold", 20);
    HIScoreLB->setColor(Color3B::RED);
    HIScoreLB->setPosition(200, 300);
    this->addChild(HIScoreLB);
    
    auto highestScoreLB = Label::createWithSystemFont("20000", "ArialRoundedMTBold", 20);
    highestScoreLB->setColor(Color3B::ORANGE);
    highestScoreLB->setPosition(300, 300);
    highestScoreLB->setString(StringUtils::format("%ld", GameManager::getInstance()->getHighestScore()));
    this->addChild(highestScoreLB);
    
    auto stageLB = Label::createWithSystemFont("STAGE", "ArialRoundedMTBold", 20);
    stageLB->setColor(Color3B::WHITE);
    stageLB->setPosition(220, 270);
    this->addChild(stageLB);
    
    stage = Label::createWithSystemFont("1", "ArialRoundedMTBold", 20);
    stage->setColor(Color3B::WHITE);
    stage->setPosition(280, 270);
    stage->setString(StringUtils::format("%d", GameManager::getInstance()->getLevel()));
    this->addChild(stage);
    
    auto playerLB = Label::createWithSystemFont("I-PLAYER", "ArialRoundedMTBold", 20);
    playerLB->setColor(Color3B::RED);
    playerLB->setPosition(145, 240);
    this->addChild(playerLB);
    
    playerScore = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    playerScore->setColor(Color3B::ORANGE);
    playerScore->setPosition(145, 210);
    playerScore->setString(StringUtils::format("%ld", GameManager::getInstance()->getScore()));
    this->addChild(playerScore);
    
    enemyAScore = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    enemyAScore->setColor(Color3B::WHITE);
    enemyAScore->setPosition(145, 180);
    enemyAScore->setVisible(false);
    this->addChild(enemyAScore);
    
    enemyBScore = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    enemyBScore->setColor(Color3B::WHITE);
    enemyBScore->setPosition(145, 150);
    enemyBScore->setVisible(false);
    this->addChild(enemyBScore);
    
    enemyCScore = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    enemyCScore->setColor(Color3B::WHITE);
    enemyCScore->setPosition(145, 120);
    enemyCScore->setVisible(false);
    this->addChild(enemyCScore);
    
    enemyDScore = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    enemyDScore->setColor(Color3B::WHITE);
    enemyDScore->setPosition(145, 90);
    enemyDScore->setVisible(false);
    this->addChild(enemyDScore);
    
    auto PTSLbA = Label::createWithSystemFont("PTS", "ArialRoundedMTBold", 20);
    PTSLbA->setColor(Color3B::WHITE);
    PTSLbA->setPosition(200, 180);
    this->addChild(PTSLbA);
    
    auto PTSLbB = Label::createWithSystemFont("PTS", "ArialRoundedMTBold", 20);
    PTSLbB->setColor(Color3B::WHITE);
    PTSLbB->setPosition(200, 150);
    this->addChild(PTSLbB);
    
    auto PTSLbC = Label::createWithSystemFont("PTS", "ArialRoundedMTBold", 20);
    PTSLbC->setColor(Color3B::WHITE);
    PTSLbC->setPosition(200, 120);
    this->addChild(PTSLbC);
    
    auto PTSLbD = Label::createWithSystemFont("PTS", "ArialRoundedMTBold", 20);
    PTSLbD->setColor(Color3B::WHITE);
    PTSLbD->setPosition(200, 90);
    this->addChild(PTSLbD);
    
    enemyAHits = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    enemyAHits->setColor(Color3B::WHITE);
    enemyAHits->setPosition(240, 180);
    enemyAHits->setVisible(false);
    this->addChild(enemyAHits);
    
    enemyBHits = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    enemyBHits->setColor(Color3B::WHITE);
    enemyBHits->setPosition(240, 150);
    enemyBHits->setVisible(false);
    this->addChild(enemyBHits);
    
    enemyCHits = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    enemyCHits->setColor(Color3B::WHITE);
    enemyCHits->setPosition(240, 120);
    enemyCHits->setVisible(false);
    this->addChild(enemyCHits);
    
    enemyDHits = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    enemyDHits->setColor(Color3B::WHITE);
    enemyDHits->setPosition(240, 90);
    enemyDHits->setVisible(false);
    this->addChild(enemyDHits);
    
    auto arrowA = Sprite::createWithSpriteFrameName("arrow.png");
    arrowA->setPosition(270, 180);
    this->addChild(arrowA);
    
    auto arrowB = Sprite::createWithSpriteFrameName("arrow.png");
    arrowB->setPosition(270, 150);
    this->addChild(arrowB);
    
    auto arrowC = Sprite::createWithSpriteFrameName("arrow.png");
    arrowC->setPosition(270, 120);
    this->addChild(arrowC);
    
    auto arrowD = Sprite::createWithSpriteFrameName("arrow.png");
    arrowD->setPosition(270, 90);
    this->addChild(arrowD);
    
    auto logoA = Sprite::createWithSpriteFrameName("enemyA11.png");
    logoA->setPosition(300, 180);
    this->addChild(logoA);
    
    auto logoB = Sprite::createWithSpriteFrameName("enemyB11.png");
    logoB->setPosition(300, 150);
    this->addChild(logoB);
    
    auto logoC = Sprite::createWithSpriteFrameName("enemyC11.png");
    logoC->setPosition(300, 120);
    this->addChild(logoC);
    
    auto logoD = Sprite::createWithSpriteFrameName("enemyD11.png");
    logoD->setPosition(300, 90);
    this->addChild(logoD);
    
    total = Label::createWithSystemFont("0", "ArialRoundedMTBold", 20);
    total->setColor(Color3B::WHITE);
    total->setPosition(240, 40);
    total->setVisible(false);
    this->addChild(total);
    
    DelayTime *delayAction = DelayTime::create(2.0f);
    auto call = CallFuncN::create(CC_CALLBACK_0(ScoreScene::showScore, this));
    auto seq = Sequence::create(delayAction, call, NULL);
    this->runAction(seq);
    
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

void ScoreScene::showScore(){
    switch (count) {
        case 0:
        {
            enemyAHits->setVisible(true);
            enemyAScore->setVisible(true);
            updateTimes = GameManager::getInstance()->getEnemyAKilled();
            totalKill += updateTimes;
            this->schedule(CC_SCHEDULE_SELECTOR(ScoreScene::updateLabel), 0.2f);
            break;
        }
        case 1:
        {
            enemyBHits->setVisible(true);
            enemyBScore->setVisible(true);
            updateTimes = GameManager::getInstance()->getEnemyBKilled();
            totalKill += updateTimes;
            this->schedule(CC_SCHEDULE_SELECTOR(ScoreScene::updateLabel), 0.2f);
            break;
        }
        case 2:
        {
            enemyCHits->setVisible(true);
            enemyCScore->setVisible(true);
            updateTimes = GameManager::getInstance()->getEnemyCKilled();
            totalKill += updateTimes;
            this->schedule(CC_SCHEDULE_SELECTOR(ScoreScene::updateLabel), 0.2f);
            break;
        }
        case 3:
        {
            enemyDHits->setVisible(true);
            enemyDScore->setVisible(true);
            updateTimes = GameManager::getInstance()->getEnemyDKilled();
            totalKill += updateTimes;
            this->schedule(CC_SCHEDULE_SELECTOR(ScoreScene::updateLabel), 0.2f);
            break;
        }
        case 4:
        {
            total->setVisible(true);
            auto totalStr = StringUtils::format("%d", totalKill);
            total->setString(totalStr);
            if (GameManager::getInstance()->getOver()) {
                DelayTime *delayAction = DelayTime::create(3.0f);
                auto call = CallFuncN::create(CC_CALLBACK_0(ScoreScene::showGameOver, this));
                auto seq = Sequence::create(delayAction, call, NULL);
                this->runAction(seq);
            }
            else{
                DelayTime *delayAction = DelayTime::create(3.0f);
                auto call = CallFuncN::create(CC_CALLBACK_0(ScoreScene::gotoNextLevel, this));
                auto seq = Sequence::create(delayAction, call, NULL);
                this->runAction(seq);
            }
            break;
        }
        default:
            break;
    }
}

void ScoreScene::updateLabel(float delta){
    switch (count) {
        case 0:
            if (--updateTimes > 0) {
                auto hitStr = StringUtils::format("%d", GameManager::getInstance()->getEnemyAKilled() - updateTimes);
                enemyAHits->setString(hitStr);
                auto scoreStr = StringUtils::format("%d", 100 * (GameManager::getInstance()->getEnemyAKilled() - updateTimes));
                enemyAScore->setString(scoreStr);
            }
            else{
                this->unschedule(CC_SCHEDULE_SELECTOR(ScoreScene::updateLabel));
                ++count;
                this->showScore();
            }
            break;
        case 1:
            if (--updateTimes > 0) {
                auto hitStr = StringUtils::format("%d", GameManager::getInstance()->getEnemyBKilled() - updateTimes);
                enemyBHits->setString(hitStr);
                auto scoreStr = StringUtils::format("%d", 200 * (GameManager::getInstance()->getEnemyBKilled() - updateTimes));
                enemyBScore->setString(scoreStr);
            }
            else{
                this->unschedule(CC_SCHEDULE_SELECTOR(ScoreScene::updateLabel));
                ++count;
                this->showScore();
            }
            break;
        case 2:
            if (--updateTimes > 0) {
                auto hitStr = StringUtils::format("%d", GameManager::getInstance()->getEnemyCKilled() - updateTimes);
                enemyCHits->setString(hitStr);
                auto scoreStr = StringUtils::format("%d", 300 * (GameManager::getInstance()->getEnemyCKilled() - updateTimes));
                enemyCScore->setString(scoreStr);
            }
            else{
                this->unschedule(CC_SCHEDULE_SELECTOR(ScoreScene::updateLabel));
                ++count;
                this->showScore();
            }
            break;
        case 3:
            if (--updateTimes > 0) {
                auto hitStr = StringUtils::format("%d", GameManager::getInstance()->getEnemyDKilled() - updateTimes);
                enemyDHits->setString(hitStr);
                auto scoreStr = StringUtils::format("%d", 400 * (GameManager::getInstance()->getEnemyDKilled() - updateTimes));
                enemyDScore->setString(scoreStr);
            }
            else{
                this->unschedule(CC_SCHEDULE_SELECTOR(ScoreScene::updateLabel));
                ++count;
                this->showScore();
            }
            break;
            
        default:
            break;
    }
}

void ScoreScene::showGameOver(){
    Size screenSize = Director::getInstance()->getVisibleSize();
    auto gameOver = Sprite::create("gameOver.png");
    this->addChild(gameOver, 1);
    gameOver->setPosition(screenSize.width * 0.5, screenSize.height * 0.5);
    
    DelayTime *delayAction = DelayTime::create(3.0f);
    auto call = CallFuncN::create(CC_CALLBACK_0(ScoreScene::gotoMainMenu, this));
    auto seq = Sequence::create(delayAction, call, NULL);
    this->runAction(seq);
}

void ScoreScene::gotoNextLevel(){
    GameManager::getInstance()->setLevel(GameManager::getInstance()->getLevel() + 1);
    auto fade = TransitionFade::create(2.0f, LevelScene::createScene(), Color3B(255, 255, 255));
    Director::getInstance()->replaceScene(fade);
}

void ScoreScene::gotoMainMenu(){
    auto fade = TransitionFade::create(2.0f, MainMenuScene::createScene(), Color3B(255, 255, 255));
    Director::getInstance()->replaceScene(fade);
}

//
//-(void) draw
//{
//    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//    ccDrawLine(CGPointMake(230, 65), CGPointMake(310, 65));
//}

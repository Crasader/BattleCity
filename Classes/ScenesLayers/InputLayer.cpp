//
//  InputLayer.cpp
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#include "InputLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "Entity.h"
#include "BulletCache.h"
#include "PlayerEntity.h"

USING_NS_CC;

bool InputLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("start.wav");
    this->addFireButton();
    this->addJoystick();
    
    this->scheduleUpdate();
    return true;
}

void InputLayer::addFireButton(){
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    fireButton = SneakyButton::create();
    fireButton->initWithRect(Rect::ZERO);
    fireButton->setIsHoldable(true);
    
    auto defaultSprite = Sprite::createWithSpriteFrameName("button-default.png");
    defaultSprite->setScale(0.5f);
    auto activatedSprite = Sprite::createWithSpriteFrameName("button-pressed.png");
    activatedSprite->setScale(0.5f);
    auto pressSprite = Sprite::createWithSpriteFrameName("button-pressed.png");
    pressSprite->setScale(0.5f);
    auto skinFireButton = SneakyButtonSkinnedBase::create();
    skinFireButton->setPosition(Vec2(screenSize.width - defaultSprite->getContentSize().width * 0.5f * defaultSprite->getScale() - 4, defaultSprite->getContentSize().height * 0.5f * defaultSprite->getScale() + 4));
    skinFireButton->setDefaultSprite(defaultSprite);
    skinFireButton->setActivatedSprite(activatedSprite);
    skinFireButton->setPressSprite(pressSprite);
    skinFireButton->setButton(fireButton);
    this->addChild(skinFireButton);
}

void InputLayer::addJoystick(){
    float stickRadius = 50;
    
    joystick = SneakyJoystick::create();
    joystick->initWithRect(Rect(0, 0, stickRadius, stickRadius));
    joystick->setAutoCenter(true);
    
    // Now with fewer directions
    joystick->setIsDPad(true);
    joystick->setNumberOfDirections(4);
    
    auto skinStick = SneakyJoystickSkinnedBase::create();
    skinStick->setPosition(Vec2(stickRadius * 1.1f, stickRadius * 1.5f));
    skinStick->setBackgroundSprite(Sprite::createWithSpriteFrameName("button-disabled.png"));
    skinStick->getBackgroundSprite()->setColor(Color3B::MAGENTA);
    skinStick->setThumbSprite(Sprite::createWithSpriteFrameName("button-disabled.png"));
    skinStick->getThumbSprite()->setScale(0.5f);
    skinStick->setJoystick(joystick);
    this->addChild(skinStick);
}

void InputLayer::update(float delta){
    if(!GameManager::getInstance()->getOver()){
        totalTime += delta;
        
        auto gameScene = GameScene::getCurrentGameScene();
        auto player = gameScene->getDefaultPlayer();
        auto bulletCache = gameScene->getBulletCache();
        if (player->isVisible()) {
            // Continuous fire
            if (fireButton->getIsActive() && !player->getReload() && totalTime > nextShotTime) {
                nextShotTime = totalTime + 0.5f;
                player->setReload(true);
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fire.wav");
                bulletCache->shootBulletFrom(player->getStartPos(), player->getBulletVelocity(), "bullet.png", true, player);
            }
            
            // Allow faster shooting by quickly tapping the fire button.
            if (!fireButton->getIsActive()) {
                nextShotTime = 0;
            }
            
            // Moving the tank with the thumbstick.
            Vec2 velocity = joystick->getVelocity() * 100;
            if (velocity.x != 0 && velocity.y != 0) {
                if (velocity.y > 80)
                {
                    player->setRotation(0);
                }
                else if (velocity.x > 80)
                {
                    player->setRotation(90);
                }
                else if (velocity.x < -80)
                {
                    player->setRotation(270);
                }
                else if(velocity.y < -80)
                {
                    player->setRotation(180);
                }
                player->updatePosition(Vec2(player->getPosition().x + velocity.x * delta, player->getPosition().y + velocity.y * delta));
            }
        }
    }
}

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
    
    return true;
}

void InputLayer::addFireButton(){
    float buttonRadius = 30;
    Size screenSize = Director::getInstance()->getVisibleSize();
    
    fireButton = SneakyButton::create();
    fireButton->initWithRect(Rect::ZERO);
    fireButton->setIsHoldable(true);
    
    auto skinFireButton = SneakyButtonSkinnedBase::create();
    skinFireButton->setPosition(Vec2(screenSize.width - buttonRadius * 1.0f, buttonRadius * 1.0f));
    skinFireButton->setDefaultSprite(Sprite::createWithSpriteFrameName("button-default.png"));
    skinFireButton->setPressSprite(Sprite::createWithSpriteFrameName("button-pressed.png"));
    skinFireButton->setButton(fireButton);
    skinFireButton->setScale(0.5f);
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

void update(float delta)

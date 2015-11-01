//
//  InputLayer.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__InputLayer__
#define __BattleCity__InputLayer__

#include "cocos2d.h"
#include "SneakyInput.h"

class InputLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(InputLayer);
    
private:
    SneakyButton* fireButton;
    SneakyJoystick* joystick;
    
    float totalTime;
    float nextShotTime;
    
    void addFireButton();
    void addJoystick();
};

#endif /* defined(__BattleCity__InputLayer__) */

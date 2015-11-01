//
//  LevelScene.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__LevelScene__
#define __BattleCity__LevelScene__

#include "cocos2d.h"

class LevelScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LevelScene);
    
private:
    virtual void onEnter();
    virtual void onExit();
    
    cocos2d::Label *levelLB;
    
    void chooseLevel();
    void beginItemTouched(Ref* pSender);
    void gotoNextLevel(Ref* pSender);
};

#endif /* defined(__BattleCity__LevelScene__) */

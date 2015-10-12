//
//  MainMenuScene.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__MainMenuScene__
#define __BattleCity__MainMenuScene__

#include "cocos2d.h"

typedef enum
{
    kTagBackGround = 0,
    kTagMoveToCenterAction,
}MenuSceneNodeTags;

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif /* defined(__BattleCity__MainMenuScene__) */

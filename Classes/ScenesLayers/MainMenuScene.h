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
    CREATE_FUNC(MainMenuScene);
    
private:
    virtual void onEnter();
    virtual void onExit();
    
    void showTankIcon(cocos2d::Ref* pSender);
    void beginItemTouched(cocos2d::Ref* pSender);
    void optionItemTouched(cocos2d::Ref* pSender);
    void setTouchEnabled(bool enabled);
    void onTouchBegan();
};

#endif /* defined(__BattleCity__MainMenuScene__) */

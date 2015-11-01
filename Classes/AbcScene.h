//
//  AbcScene.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__AbcScene__
#define __BattleCity__AbcScene__

#include "cocos2d.h"

class AbcScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(AbcScene);
    
private:
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__BattleCity__AbcScene__) */

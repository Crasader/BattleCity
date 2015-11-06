//
//  ScoreScene.h
//  BattleCity
//
//  Created by Jay on 15/10/10.
//
//

#ifndef __BattleCity__ScoreScene__
#define __BattleCity__ScoreScene__

#include "cocos2d.h"

class ScoreScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ScoreScene);
    
private:
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__BattleCity__ScoreScene__) */

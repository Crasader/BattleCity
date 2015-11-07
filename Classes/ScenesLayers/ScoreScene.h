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
    
    cocos2d::Label* highestScore;
    cocos2d::Label* stage;
    cocos2d::Label* playerScore;
    cocos2d::Label* enemyAHits;
    cocos2d::Label* enemyBHits;
    cocos2d::Label* enemyCHits;
    cocos2d::Label* enemyDHits;
    cocos2d::Label* enemyAScore;
    cocos2d::Label* enemyBScore;
    cocos2d::Label* enemyCScore;
    cocos2d::Label* enemyDScore;
    cocos2d::Label* total;
    int count;//label标记更新次序
    int updateTimes;
    int totalKill;
    
    void showScore();
    void updateLabel(float delta);
    void showGameOver();
    void gotoNextLevel();
    void gotoMainMenu();
};

#endif /* defined(__BattleCity__ScoreScene__) */

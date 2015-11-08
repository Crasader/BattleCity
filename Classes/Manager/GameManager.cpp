//
//  GameManager.cpp
//  BattleCity
//
//  Created by Jay on 15/10/25.
//
//

#include "GameManager.h"

using namespace cocos2d;

static GameManager *_sharedGameManager = NULL;

GameManager* GameManager::getInstance()
{
    if (! _sharedGameManager)
    {
        _sharedGameManager = new GameManager();
        _sharedGameManager->init();
    }
    
    return _sharedGameManager;
}

GameManager::~GameManager(void)
{
}

bool GameManager::init(void)
{
    _level = 1;
    lives = 30;
    _totalLevels = 4;
    over = false;
    chooseLevel = true;
    _highestScore = 20000;
    score = 0;
    enemyAKilled = 0;
    enemyBKilled = 0;
    enemyCKilled = 0;
    enemyDKilled = 0;
    enemyRemain = 20;
    currentEnemyCount = 0;
    return true;
}

/// highestScore getter
long GameManager::getHighestScore()
{
    if (_highestScore > score)
    {
        return _highestScore;
    }
    else
    {
        _highestScore = score;
        return score;
    }
}

/// highestScore setter
void GameManager::setHighestScore(long highestScore)
{
    _highestScore = highestScore;
}

/// level getter
int GameManager::getLevel()
{
    return _level;
}

/// level setter
void GameManager::setLevel(int level)
{
    if (level > _totalLevels) {
        _level = 1;
    }
    else
    {
        _level = level;
    }
}

void GameManager::resetGame(){
    chooseLevel = true;
    over = false;
    lives = 30;
    _level = 1;
    score = 0;
}

void GameManager::resetLevel(){
    enemyAKilled = 0;
    enemyBKilled = 0;
    enemyCKilled = 0;
    enemyDKilled = 0;
    enemyRemain = 20;
    currentEnemyCount = 0;
}

void GameManager::addCurrentEnemyCountBy(int amount){
    currentEnemyCount += amount;
}

void GameManager::addScoreBy(long amount){
    score += amount;
}

void GameManager::addEnemyAKilled(long amount){
    enemyAKilled += amount;
}

void GameManager::addEnemyBKilled(long amount){
    enemyBKilled += amount;
}

void GameManager::addEnemyCKilled(long amount){
    enemyCKilled += amount;
}

void GameManager::addEnemyDKilled(long amount){
    enemyDKilled += amount;
}

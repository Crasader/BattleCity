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
    _lives = 30;
    _totalLevels = 4;
    over = false;
    _chooseLevel = true;
    _highestScore = 20000;
    _score = 0;
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
    if (_highestScore > _score)
    {
        return _highestScore;
    }
    else
    {
        _highestScore = _score;
        return _score;
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

bool GameManager::getChooseLevel()
{
    return _chooseLevel;
}

void GameManager::setChooseLevel(bool chooseLevel)
{
    _chooseLevel = chooseLevel;
}

void GameManager::resetGame(){
    _chooseLevel = true;
    over = false;
    _lives = 30;
    _level = 1;
    _score = 0;
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

long GameManager::getScore(){
    return _score;
}

void GameManager::setScore(long score){
    _score = score;
}

void GameManager::addScoreBy(long amount){
    _score += amount;
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

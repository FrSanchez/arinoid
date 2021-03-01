//
//  GameScene.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/11/21.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "Arena.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

class GameScene : public cocos2d::Scene
{
private:
    int _level;
    int _score = 0;
    int _lives = 3;
    Paddle* _paddle;
    void initRound();
    void die();
    void endScene(float dt);
    void winLevel();
    void initLevel();
    cocos2d::Node* createShadow(cocos2d::Vec2 pos, cocos2d::Color4F color, cocos2d::Size size);
    cocos2d::Sprite* addLifeSprite(int pos);
    int getGainThreshold();
    cocos2d::Node* getContact(cocos2d::PhysicsBody *a, cocos2d::PhysicsBody *b, int tag);
    Ball* addBall();
    void loseBall(Ball* ball);
    
    float initialVelocity;
    
    int _brickCount;
    bool _debugDraw = false;
    int _gainLevelThreshold;
    int _ballCount = 0;
    cocos2d::Vector<cocos2d::Sprite*> _livesSprites;

    void removeBalls();
    void addToScore(int value);
    
    static const int maxLevel = 19;

    constexpr static const int levels[][24][12] = {
        {// level1
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {6,6,6,6,6,6,6,6,6,6,6,6},
        {10,10,10,10,10,10,10,10,10,10,10,10},
        {2,2,2,2,2,2,2,2,2,2,2,2},
        {8,8,8,8,8,8,8,8,8,8,8,8},
        {4,4,4,4,4,4,4,4,4,4,4,4},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level2
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {4,4,4,4,4,4,4,4,4,4,4,4},
        {10,1,3,2,8,7,6,10,1,3,2,8},
        {10,1,3,2,8,7,6,10,1,3,2,0},
        {10,1,3,2,8,7,6,10,1,3,0,0},
        {10,1,3,2,8,7,6,10,1,0,0,0},
        {10,1,3,2,8,7,6,10,0,0,0,0},
        {10,1,3,2,8,7,6,0,0,0,0,0},
        {10,1,3,2,8,7,0,0,0,0,0,0},
        {10,1,3,2,8,0,0,0,0,0,0,0},
        {10,1,3,2,0,0,0,0,0,0,0,0},
        {10,1,3,0,0,0,0,0,0,0,0,0},
        {10,1,0,0,0,0,0,0,0,0,0,0},
        {10,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level3
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {10,10,10,10,10,10,10,10,2,2,2,2},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {2,2,2,2,2,2,2,2,2,2,2,2},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {2,2,2,10,10,10,10,10,10,10,10,10},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {6,6,6,6,6,6,6,6,6,6,6,6},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {10,10,10,10,10,10,10,10,10,9,9,9},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {8,8,8,8,8,8,8,8,8,8,8,8},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {9,9,9,10,10,10,10,10,10,10,10,10},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level4
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,6,3,10,4,0,0,6,3,10,4,0},
        {0,8,10,3,2,0,0,8,10,3,2,0},
        {0,10,8,6,3,0,0,10,8,6,3,0},
        {0,3,6,8,10,0,0,3,6,8,10,0},
        {0,2,3,10,8,0,0,2,3,10,8,0},
        {0,4,10,3,6,0,0,6,3,10,4,0},
        {0,10,4,2,3,0,0,8,10,3,2,0},
        {0,3,2,4,10,0,0,10,8,6,3,0},
        {0,6,3,10,4,0,0,3,6,8,10,0},
        {0,8,10,3,2,0,0,2,3,10,8,0},
        {0,10,8,6,3,0,0,4,2,3,10,0},
        {0,3,6,8,10,0,0,2,4,10,3,0},
        {0,2,3,10,8,0,0,3,10,4,2,0},
        {0,4,10,3,6,0,0,10,3,2,4,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level5
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,4,0,0,4,0,0,0,0},
        {0,0,0,0,4,0,0,4,0,0,0,0},
        {0,4,0,4,0,0,0,0,4,0,4,0},
        {0,4,0,4,0,0,0,0,4,0,4,0},
        {0,4,0,4,4,4,4,4,4,0,4,0},
        {0,4,4,4,4,4,4,4,4,4,4,0},
        {0,4,4,4,4,4,4,4,4,4,4,0},
        {0,0,4,4,8,4,4,8,4,4,0,0},
        {0,0,4,4,8,4,4,8,4,4,0,0},
        {0,0,0,4,4,4,4,4,4,0,0,0},
        {0,0,0,4,4,4,4,4,4,0,0,0},
        {0,0,0,0,10,0,0,10,0,0,0,0},
        {0,0,0,0,10,0,0,10,0,0,0,0},
        {0,0,0,10,0,0,0,0,10,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level6
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {10,0,5,0,5,0,0,5,0,5,0,10},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {2,0,5,6,5,6,6,5,6,5,0,2},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {2,0,8,0,3,0,0,3,0,8,0,2},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level7
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,10,3,0,0,0,0},
        {0,0,0,0,1,2,3,10,6,0,0,0},
        {0,0,0,0,10,3,2,1,10,0,0,0},
        {0,0,0,8,3,10,1,2,3,10,0,0},
        {0,0,0,3,8,6,10,3,2,1,0,0},
        {0,0,0,10,6,8,3,10,1,2,0,0},
        {0,0,0,1,10,3,8,6,10,3,0,0},
        {0,0,0,2,3,10,6,8,3,10,0,0},
        {0,0,0,3,2,1,10,3,8,6,0,0},
        {0,0,0,0,1,2,3,10,6,0,0,0},
        {0,0,0,0,10,3,2,1,10,0,0,0},
        {0,0,0,0,0,10,1,2,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level8
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,5,0,0,5,0,0,5,0,0,5,0},
        {0,5,5,0,0,0,0,0,0,5,5,0},
        {0,0,0,0,0,6,6,0,0,0,0,0},
        {0,0,0,0,5,3,3,5,0,0,0,0},
        {0,0,5,0,0,8,8,0,0,5,0,0},
        {0,0,0,0,0,2,2,0,0,0,0,0},
        {0,0,5,0,0,5,5,0,0,5,0,0},
        {0,0,0,0,5,3,3,5,0,0,0,0},
        {0,0,0,0,0,6,6,0,0,0,0,0},
        {0,5,5,0,0,0,0,0,0,5,5,0},
        {0,5,0,0,5,0,0,5,0,0,5,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level9
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,6,2,2,2,2,10,0,0,0},
        {0,0,0,6,1,3,1,3,10,0,0,0},
        {0,0,0,6,3,1,3,1,10,0,0,0},
        {0,0,0,6,1,3,1,3,10,0,0,0},
        {0,0,0,6,3,1,3,1,10,0,0,0},
        {0,0,0,6,1,3,1,3,10,0,0,0},
        {0,0,0,6,2,2,2,2,10,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,5,5,5,0,0,0,0,5,5,5,0},
        {0,5,2,5,0,0,0,0,5,2,5,0},
        {0,5,3,5,0,0,0,0,5,3,5,0},
        {0,5,0,5,0,0,0,0,5,0,5,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level10
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,5,5,5,5,5,5,5,5,5,5,5},
        {0,5,0,0,0,0,0,0,0,0,0,0},
        {0,5,0,0,0,0,0,0,0,0,0,0},
        {0,5,0,0,0,0,0,0,0,0,0,0},
        {0,5,0,0,0,0,2,0,0,0,0,0},
        {0,5,0,0,0,2,1,2,0,0,0,0},
        {0,5,0,0,2,1,2,1,2,0,0,0},
        {0,5,0,2,1,2,4,2,1,2,0,0},
        {0,5,0,0,2,1,2,1,2,0,0,0},
        {0,5,0,0,0,2,1,2,0,0,0,0},
        {0,5,0,0,0,0,2,0,0,0,0,0},
        {0,5,0,0,0,0,0,0,0,0,0,0},
        {0,5,0,0,0,0,0,0,0,0,0,0},
        {0,5,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,5,0,0,0,0,0,0,0,0,0,0}}
        ,{// level11
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,4,4,4,4,4,4,4,4,4,4,0},
        {0,4,0,0,0,0,0,0,0,0,4,0},
        {0,4,0,4,4,4,4,4,4,0,4,0},
        {0,4,0,4,0,0,0,0,4,0,4,0},
        {0,4,0,4,0,4,4,0,4,0,4,0},
        {0,4,0,4,0,4,4,0,4,0,4,0},
        {0,4,0,4,0,0,0,0,4,0,4,0},
        {0,4,0,4,4,4,4,4,4,0,4,0},
        {0,4,0,0,0,0,0,0,0,0,4,0},
        {0,4,4,4,4,4,4,4,4,4,4,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level12
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,5,5,5,5,5,5,5,5,5,5,5},
        {0,5,0,0,0,0,5,0,0,0,0,10},
        {0,5,1,0,0,0,5,0,0,0,0,0},
        {0,5,0,0,5,0,5,0,0,5,0,0},
        {0,5,0,0,5,0,5,3,3,5,0,0},
        {0,5,0,7,5,0,5,0,0,5,0,0},
        {0,5,0,0,5,0,5,8,8,5,0,0},
        {0,5,0,0,5,0,5,0,0,5,0,0},
        {0,5,0,0,5,0,5,0,0,5,0,0},
        {0,5,0,0,5,0,0,0,0,5,0,0},
        {0,5,3,0,5,0,0,0,0,5,0,0},
        {0,0,0,0,5,0,0,0,0,5,10,0},
        {5,5,5,5,5,5,5,5,5,5,5,5},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level13
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,9,9,0,10,10,10,10,0,9,9,0},
        {0,10,10,0,9,9,9,9,0,10,10,0},
        {0,8,8,0,2,2,2,2,0,8,8,0},
        {0,3,3,0,6,6,6,6,0,3,3,0},
        {0,6,6,0,3,3,3,3,0,6,6,0},
        {0,2,2,0,8,8,8,8,0,2,2,0},
        {0,9,9,0,10,10,10,10,0,9,9,0},
        {0,10,10,0,9,9,9,9,0,10,10,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level14
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {5,0,0,0,0,0,0,0,0,0,0,5},
        {8,8,8,8,8,8,8,8,8,8,8,8},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {8,8,8,8,8,8,8,8,8,8,8,8},
        {5,0,0,0,0,0,0,0,0,0,0,5},
        {2,4,4,4,4,4,4,4,4,4,4,2},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {2,2,2,2,2,2,2,2,2,2,2,2},
        {5,0,0,0,0,0,0,0,0,0,0,5},
        {10,4,4,4,4,4,4,4,4,4,4,10},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {2,2,2,2,2,2,2,2,2,2,2,2},
        {5,0,0,0,0,0,0,0,0,0,0,5},
        {8,4,4,4,4,4,4,4,4,4,4,8},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level15
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,4,4,4,4,1,1,1,1},
        {1,1,1,4,10,4,4,3,4,1,1,1},
        {1,1,4,10,10,4,4,3,3,4,1,1},
        {1,4,10,10,10,4,4,3,3,3,4,1},
        {1,4,10,10,10,4,4,3,3,3,4,1},
        {1,4,10,10,10,4,4,3,3,3,4,1},
        {1,4,10,10,10,4,4,3,3,3,4,1},
        {1,4,10,10,10,4,4,3,3,3,4,1},
        {1,4,10,10,10,4,4,3,3,3,4,1},
        {1,4,10,10,4,0,0,4,3,3,4,1},
        {1,4,10,4,4,0,0,4,4,3,4,1},
        {1,4,4,4,0,0,0,0,4,4,4,1},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level16
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {7,0,0,0,0,0,0,0,0,0,0,7},
        {0,7,7,0,0,0,0,0,0,7,7,0},
        {2,0,0,7,7,0,0,7,7,0,0,2},
        {0,2,2,0,0,5,5,0,0,2,2,0},
        {8,0,0,2,2,0,0,2,2,0,0,8},
        {0,8,8,0,0,5,5,0,0,8,8,0},
        {3,0,0,8,8,0,0,8,8,0,0,3},
        {0,3,3,0,0,5,5,0,0,3,3,0},
        {10,0,0,3,3,0,0,3,3,0,0,10},
        {0,10,10,0,0,5,5,0,0,10,10,0},
        {9,0,0,10,10,0,0,10,10,0,0,9},
        {0,9,9,0,0,5,5,0,0,9,9,0},
        {0,0,0,9,9,0,0,9,9,0,0,0},
        {0,0,0,0,0,5,5,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level17
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,5,0,0,0,0,0},
        {0,0,0,0,0,5,5,5,0,0,0,0},
        {0,0,0,0,0,5,0,5,0,0,0,0},
        {0,0,0,0,0,4,0,0,0,0,0,0},
        {0,0,0,0,0,4,0,0,0,0,0,0},
        {0,4,0,4,0,4,0,4,0,4,0,0},
        {0,2,2,9,9,9,9,9,3,3,0,0},
        {0,2,2,9,9,9,9,9,3,3,0,0},
        {0,2,2,9,9,9,9,9,3,3,0,0},
        {0,0,2,2,9,9,9,3,3,0,0,0},
        {0,0,0,2,2,4,3,3,0,0,0,0},
        {0,0,0,0,0,4,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level18
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {7,5,5,5,3,0,0,3,5,5,5,7},
        {7,0,5,0,3,0,0,3,0,5,0,7},
        {7,0,5,0,3,0,0,3,0,5,0,7},
        {7,0,5,0,3,0,0,3,0,5,0,7},
        {7,0,5,0,3,0,0,3,0,5,0,7},
        {7,0,5,0,3,0,0,3,0,5,0,7},
        {7,0,5,0,3,4,4,3,0,5,0,7},
        {7,0,5,0,5,10,10,5,0,5,0,7},
        {7,0,5,5,10,10,10,10,5,5,0,7},
        {7,0,5,10,10,10,10,10,10,5,0,7},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
        ,{// level19
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,5,5,5,5,5,5,5,5,0,0},
        {0,0,3,8,2,5,6,2,8,3,0,0},
        {0,0,3,8,2,6,5,2,8,3,0,0},
        {0,0,3,8,2,5,6,2,8,3,0,0},
        {0,0,3,8,2,6,5,2,8,3,0,0},
        {0,0,3,8,2,5,6,2,8,3,0,0},
        {0,0,3,8,2,6,5,2,8,3,0,0},
        {0,0,3,8,2,5,6,2,8,3,0,0},
        {0,0,3,8,2,6,5,2,8,3,0,0},
        {0,0,3,8,2,5,6,2,8,3,0,0},
        {0,0,5,5,5,5,5,5,5,5,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}}
    };
    
public:
    static cocos2d::Scene* createScene();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    virtual bool init();
    void makeLevel(Arena* arena, int level);
    void extraBallsPowerUp(void);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
};
#endif /* GameScene_hpp */

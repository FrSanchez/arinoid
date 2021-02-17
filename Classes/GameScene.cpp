//
//  GameScene.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/11/21.
//

#include "GameScene.h"
#include "Arena.h"
#include "Paddle.h"
#include "Brick.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    Brick::tiles = new (std::nothrow) cocos2d::Rect[8] {
        {225, 193, 31, 16},
        {225, 225, 31, 16},
        {225, 257, 31, 16},
        {225, 289, 31, 16},
        {257, 193, 31, 16},
        {257, 225, 31, 16},
        {257, 257, 31, 16},
        {257, 289, 31, 16}
    };
    
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto arena = Arena::create();
    arena->setPosition(Vec2(0, 96));
    arena->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(arena);
    
    auto paddle = Paddle::create();
    arena->addChild(paddle);
    paddle->setPosition(Vec2(50, 32));
    

    return true;
}

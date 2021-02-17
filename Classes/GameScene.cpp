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

std::string itoa(int value, int base);

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    
    
    brickTiles = new (std::nothrow) cocos2d::Rect[] {
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
    paddle->setPosition(Vec2(size.width / 2, 32));
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    makeLevel();
    
    return true;
}

void GameScene::makeLevel()
{
    int level0[24][12] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
        {0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
        {0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
        {0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
         
    for (int y = 0; y < 24; y++) {
        for(int x = 0; x < 12; x++) {
            if (level0[y][x] > 0) {
                auto brick = Brick::create(Vec2(x + 1, y + 10), brickTiles[level0[y][x] - 1]);
                addChild(brick);
            }
        }
    }
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    auto amask = itoa(a->getCategoryBitmask(), 2);
    auto bmask = itoa(b->getCategoryBitmask(), 2);
    log("a category %s ; b category %s", amask.c_str(), bmask.c_str());
//    PhysicsBody* body = (a->getCategoryBitmask() == 0x04 || a->getCategoryBitmask() == 0x08) ? a : b;
//    CC_ASSERT(body->getCategoryBitmask() == 0x04 || body->getCategoryBitmask() == 0x08);
    
    return true;
}

/**
     * C++ version 0.4 std::string style "itoa":
     * Contributions from Stuart Lowe, Ray-Yuan Sheu,

     * Rodrigo de Salvo Braz, Luc Gallant, John Maloney
     * and Brian Hunt
     */
std::string itoa(int value, int base) {

    std::string buf;

    // check that the base if valid
    if (base < 2 || base > 16) return buf;

    enum { kMaxDigits = 35 };
    buf.reserve( kMaxDigits ); // Pre-allocate enough space.


    int quotient = value;

    // Translating number to string with base:
    do {
        buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
        quotient /= base;
    } while ( quotient );

    // Append the negative sign
    if ( value < 0) buf += '-';

    std::reverse( buf.begin(), buf.end() );
    return buf;
}


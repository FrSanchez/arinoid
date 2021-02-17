//
//  Brick.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/16/21.
//

#include "Brick.h"

USING_NS_CC;

Brick* Brick::create(cocos2d::Vec2 pos, Rect rect)
{
    Brick *pRet = new(std::nothrow) Brick(); \
    if (pRet && pRet->init(pos, rect)) \
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool Brick::init(cocos2d::Vec2 pos, Rect rect)
{
    initWithFile("arinoid_master.png", rect);
    setPosition(Vec2(pos.x * rect.size.width, pos.y * rect.size.height));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    auto pb = PhysicsBody::createBox(Size(57,11));
    pb->setDynamic(false);
    pb->setGravityEnable(false);
    pb->setCategoryBitmask(0x0f);    // 0001
    pb->setContactTestBitmask(0xff); // 1000
    pb->setCollisionBitmask(0xff);   // 0001

    return true;
}

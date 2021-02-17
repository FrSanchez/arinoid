//
//  Brick.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/16/21.
//

#include "Brick.h"

Brick* Brick::create(cocos2d::Vec2 pos, int color)
{
    Brick *pRet = new(std::nothrow) Brick(); \
    if (pRet && pRet->init(pos, color)) \
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

bool Brick::init(cocos2d::Vec2 pos, int color)
{
    
}

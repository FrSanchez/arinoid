//
//  PowerUp.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/18/21.
//

#include "PowerUp.h"

USING_NS_CC;

PowerUp::PowerUp(char type) : _type(type)
{
}

PowerUp* PowerUp::create(char type)
{
    PowerUp *pRet = new(std::nothrow) PowerUp(type);
    if (pRet && pRet->init())
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

bool PowerUp::init()
{
    Vector<SpriteFrame*> animFrames(7);
    auto cache = SpriteFrameCache::getInstance();
    char tmp[50];
    
    for (int i = 0; i < 7; i++) {
        sprintf(tmp, "%c%d", _type, i );
        if (i == 0) {
            bool done = initWithSpriteFrameName(tmp);
            if (!done) {
                return false;
            }
        }
        auto frame = cache->getSpriteFrameByName(tmp);
        if (!frame) {
            return false;
        }
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    runAction(RepeatForever::create(Animate::create(animation)));
    return true;
}

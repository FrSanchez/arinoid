//
//  ExtraPower.cpp
//  Arinoid
//
//  Created by Francisco Sanchez on 2/24/21.
//

#include "ExtraPower.h"

USING_NS_CC;

ExtraPower::ExtraPower(char type) :
_type(tolower(type)),
_callback(nullptr)
{
    
}

CallbacksMap ExtraPower::callbacksMap ={};

ExtraPower* ExtraPower::createWithType(char type )
{
    auto *pRet = new(std::nothrow) ExtraPower(type);
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

bool ExtraPower::init()
{
    auto name = StringUtils::format("powerup-%c", _type);
    initWithSpriteFrameName(name);
    auto pb = PhysicsBody::createCircle(_contentSize.width / 2,  PhysicsMaterial(1.0f, 0.1f, 0.0f));
    pb->setDynamic(false);
    pb->setGravityEnable(false);
    pb->setCategoryBitmask(0x10);    // 0010
    pb->setContactTestBitmask(0x0C); // 0110 contact paddle and border
    pb->setCollisionBitmask(0x0C);   // 0110
    pb->setVelocity(Vec2(0, -5 * _contentSize.height ));
    addComponent(pb);
    setTag(POWERUP_TAG);
    
    if (ExtraPower::callbacksMap.find(_type) != ExtraPower::callbacksMap.end()) {
        _callback = callbacksMap.find(_type)->second;
    } else {
        log("WARNING powerup \"%c\" is not enabled!", _type);
    }
    
//    auto actionBy = RotateBy::create(2, 0.0f, 360);
//    auto actionByBack = actionBy->reverse();
//    runAction( Sequence::create(actionBy, actionByBack, nullptr) );

    return true;
}

void ExtraPower::die()
{
    this->removeFromParentAndCleanup(true);
}

void ExtraPower::caught()
{
    auto seq = Sequence::create(ResizeTo::create(0.1, Size(6, 6)),
                                CallFunc::create([&](){
        this->removeFromParentAndCleanup(true);
        if (_callback != nullptr) {
            _callback();
        }
    }), nullptr);
    this->runAction(seq);
}

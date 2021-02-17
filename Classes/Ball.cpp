//
//  Ball.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/17/21.
//

#include "Ball.h"

USING_NS_CC;

bool Ball::init()
{
    initWithFile("arinoid_master.png", Rect(428, 300, 11, 11));
    setPosition(Vec2(-getContentSize().width / 2, 0));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    auto pb = PhysicsBody::createBox(Size(11,11));
    pb->setGravityEnable(false);
    pb->setDynamic(true);
    pb->setCategoryBitmask(0x08);
    pb->setContactTestBitmask(0xff);
    pb->setCollisionBitmask(0xff);   

    addComponent(pb);
}

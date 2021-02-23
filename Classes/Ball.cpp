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
    initWithSpriteFrameName("ballGrey");
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setTag(BALL_TAG);
    
    auto pb = PhysicsBody::createCircle(_contentSize.width / 2.5, PhysicsMaterial(0.1f, 1, 0.0f));
    pb->setGravityEnable(false);
    pb->setDynamic(true);
    pb->setCategoryBitmask(0x01);
    pb->setContactTestBitmask(0x0f);
    pb->setCollisionBitmask(0x0f);

    addComponent(pb);
        
    return true;
}

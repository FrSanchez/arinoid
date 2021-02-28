//
//  Ball.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/17/21.
//

#include "Ball.h"

USING_NS_CC;

Ball::~Ball()
{
}

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
    
    schedule(CC_SCHEDULE_SELECTOR(Ball::streakUpdate));
        
    return true;
}

void Ball::pause()
{
    _velocity = getPhysicsBody()->getVelocity();
    getPhysicsBody()->setVelocity(Vec2::ZERO);
}

void Ball::unPause()
{
    getPhysicsBody()->setVelocity(_velocity);
}

void Ball::streakUpdate(float dt)
{
    if (isVisible()) {
        auto shadow = createShadow(getPosition(), Color4F::GRAY, getContentSize());
        getParent()->addChild(shadow);
        Rect rect = ((Arena*)getParent())->getArenaRect();
        if (getPosition().y <= 0) {
            log("ball lost!");
            if (_callback != nullptr) {
                _callback(this);
            }
        }
    }

}

Node* Ball::createShadow(Vec2 pos, Color4F color, Size size)
{
    auto draw = DrawNode::create();
    draw->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    draw->setPosition(pos);
    
    Vec2 vel = getPhysicsBody()->getVelocity();
    float speedDelta = 452 / vel.getLength();
    getPhysicsBody()->setVelocity( vel * speedDelta);
    

    draw->drawSolidCircle(Vec2::ZERO, size.width / 2 , CC_DEGREES_TO_RADIANS(90), 20, 0.9f, 0.9f, color);
    draw->setOpacity(128);
    auto seq = Sequence::create(FadeOut::create(0.15), CallFunc::create([&, draw](){
        draw->removeFromParentAndCleanup(true);
    }), nullptr);
    draw->runAction(seq);
    return draw;
//    draw->scheduleOnce([&](float dt) {
//    }, 1, "won");
}

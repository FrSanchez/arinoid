//
//  Paddle.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/14/21.
//

#include "Paddle.h"

USING_NS_CC;

bool Paddle::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    initWithFile("arinoid_master.png", Rect(260, 143, 57, 11));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    auto pb = PhysicsBody::createBox(Size(57,11));
    pb->setDynamic(false);
    pb->setGravityEnable(false);
    pb->setCategoryBitmask(0x04);    // 0001
    pb->setContactTestBitmask(0xff); // 1000
    pb->setCollisionBitmask(0xff);   // 0001

    addComponent(pb);

    // Make sprite1 touchable
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode))
        {
//            target->setOpacity(180);
            return true;
        }
        return false;
    };
    
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        auto newPos = target->getPosition() + touch->getDelta();
        if (newPos.x > 31 && newPos.x < 372) {
            target->setPosition(newPos.x, target->getPosition().y);
        }
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

//        target->setOpacity(255);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    return true;
}

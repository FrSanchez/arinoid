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
    
    _active = false;
    initWithSpriteFrameName("paddleRed");
    setPaddleImage(paddleImages::NORMAL);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    auto pb = PhysicsBody::createBox(getContentSize(), PhysicsMaterial(0.1f, 1.05, 0.0f) );
    pb->setDynamic(false);
    pb->setGravityEnable(false);
    pb->setCategoryBitmask(0x04);    // 0100
    pb->setContactTestBitmask(0x01); // 0001
    pb->setCollisionBitmask(0x01);   // 0110
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
    
    listener1->onTouchMoved = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        auto newPos = target->getPosition() + touch->getDelta();
        if (newPos.x > minX && newPos.x < maxX) {
            target->setPosition(newPos.x, target->getPosition().y);
        }
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    return true;
}

void Paddle::setArenaWidth(float width)
{
    minX = getContentSize().width;
    maxX = width - getContentSize().width ;
}

void Paddle::die(std::function<void(void)> callback)
{
//    Vector<SpriteFrame*> animFrames(3);
//    auto frameCache = SpriteFrameCache::getInstance();
//    animFrames.pushBack( frameCache->getSpriteFrameByName("paddle3"));
//    animFrames.pushBack( frameCache->getSpriteFrameByName("paddle2"));
//    animFrames.pushBack( frameCache->getSpriteFrameByName("paddle1"));
//    auto animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
//    auto seq = Sequence::create(Animate::create(animation), CallFunc::create([&, callback](){
//        this->setVisible(false);
//        if (callback != nullptr)
//        {
//            callback();
//        }
//    }), nullptr);
//    runAction(seq);
    
    scheduleOnce([&, callback](float dt) {
        if (callback) {
            callback();
        }
    }, 1, "died");
    _active = false;
    
    auto seq = Sequence::create(ResizeTo::create(0.1, Size(64, 32)),
                                Spawn::createWithTwoActions(
                                ResizeTo::create(0.2, Size(100, 25)), CallFunc::create([&](){
        auto _emitter = ParticleExplosion::create();
        _emitter->retain();
        _emitter->setSpeed(200);
        _emitter->setPosition(getPosition());
        getParent()->addChild(_emitter);
        _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("stars.png") );
        _emitter->setAutoRemoveOnFinish(true);
        _emitter->setDuration(0.5);
        setVisible(false);
    })), nullptr);
    this->runAction(seq);
}

void Paddle::start()
{
    _active = true;
    setVisible(true);
    this->setSpriteFrame(_currentFrame);
}

void Paddle::setPaddleImage(paddleImages image)
{
    _currentFrame = tiles[image];
//    switch(image)
//    {
//    case paddleImages::NORMAL:
//            _currentFrame = "paddle";
//        break;
//    case paddleImages::SMALL:
//            _currentFrame = "paddleSmall";
//        break;
//    case paddleImages::LARGE:
//            _currentFrame = "paddleLarge";
//        break;
//    case paddleImages::FIRE:
//            _currentFrame = "paddleFire";
//        break;
//    }
}

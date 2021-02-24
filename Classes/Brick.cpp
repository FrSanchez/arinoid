//
//  Brick.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/16/21.
//

#include "Brick.h"

USING_NS_CC;

const std::vector<std::string> Brick::tiles({
    "element_blue_rectangle_glossy",
    "element_dark_blue_rectangle_glossy",
    "element_green_rectangle_glossy",
    "element_grey_rectangle_glossy",
    "element_orange_rectangle_glossy",
    "element_pink_rectangle_glossy",
    "element_purple_rectangle_glossy",
    "element_red_rectangle_glossy",
    "element_white_rectangle_glossy",
    "element_yellow_rectangle_glossy"
});

Brick* Brick::create(cocos2d::Vec2 pos, int value)
{
    if (value < 0)
        return nullptr;
    value %= Brick::tiles.size();
    Brick *pRet = new(std::nothrow) Brick();
    if (pRet && pRet->init(pos, value))
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

void Brick::remove()
{
    auto pb = getPhysicsBody();
    removeComponent(pb);
    auto emitter = ParticleFlower::create();
    emitter->retain();
    emitter->isAutoRemoveOnFinish();
    emitter->setSpeed(200);
    emitter->setPosition(getPosition());
    emitter->setDuration(0.5);
    getParent()->addChild(emitter);
    emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("stars.png") );

    auto seq = Sequence::create(ResizeBy::create(0.1, Size(32, 32)), ResizeTo::create(0.2, Size(32, 16)), CallFunc::create([&, emitter](){
        this->removeFromParentAndCleanup(true);
    }), nullptr);
    this->runAction(seq);
}

bool Brick::init(cocos2d::Vec2 pos, int value)
{
    value %= tiles.size();
    initWithSpriteFrameName(tiles.at(value));
    setTag(TAG_BRICK);
    setPosition(Vec2(pos.x * _contentSize.width, pos.y * _contentSize.height));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    BrickData *data = new BrickData{value, 0};
    if (value == 9) {
        data->value = value * 10;
        data->hits = 1;
        data->frame = Brick::tiles[value];
    }
    setUserData(data);
    
    auto pb = PhysicsBody::createBox(_contentSize,  PhysicsMaterial(0.1f, 0.9995, 0.0f));
    pb->setDynamic(false);
    pb->setGravityEnable(false);
    pb->setCategoryBitmask(0x02);    // 0010
    pb->setContactTestBitmask(0x01); // 1000
    pb->setCollisionBitmask(0x01);   // 0001
    addComponent(pb);

    return true;
}

void Brick::updateImage()
{
    auto *data = static_cast<Brick::BrickData *>(getUserData());
    this->setSpriteFrame(data->frame);
}

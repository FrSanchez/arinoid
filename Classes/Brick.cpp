//
//  Brick.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/16/21.
//

#include "Brick.h"

USING_NS_CC;

Brick* Brick::create(cocos2d::Vec2 pos, int value)
{
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

bool Brick::init(cocos2d::Vec2 pos, int value)
{
    initWithSpriteFrameName(Brick::tiles[value-1]);
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
    
    auto pb = PhysicsBody::createBox(Size(57,11),  PhysicsMaterial(0.1f, 0.9995, 0.0f));
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

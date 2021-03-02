//
//  Brick.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/16/21.
//

#include "Brick.h"

USING_NS_CC;

const std::vector<Brick::BrickData> Brick::metadata({
    {"element_blue_rectangle_glossy", 70, 0},
    {"element_dark_blue_rectangle_glossy", 100, 0},
    {"element_green_rectangle_glossy", 80, 0},
    {"element_grey_rectangle_glossy", 50, 1},
    {"element_yellow_rectangle_glossy", 0, 0x7fffffff},
    {"element_pink_rectangle_glossy", 110, 0},
    {"element_purple_rectangle_glossy", 120, 0},
    {"element_red_rectangle_glossy", 90, 0},
    {"element_white_rectangle_glossy", 50, 0},
    {"element_orange_rectangle_glossy", 60, 0},
});

Brick* Brick::create(cocos2d::Vec2 pos, int value)
{
    if (value < 0)
        return nullptr;
    value %= Brick::metadata.size();
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

void Brick::hit()
{
    auto seq = Sequence::create(ResizeTo::create(0.1, Size(12, 6)), ResizeTo::create(0.2, Size(64, 32)),
                                ResizeTo::create(0, _size0), nullptr);
    this->runAction(seq);

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

    auto seq = Sequence::create(ResizeTo::create(0.1, Size(12, 6)), ResizeTo::create(0.2, Size(96, 32)),
                                CallFunc::create([&](){
        this->removeFromParentAndCleanup(true);
    }), nullptr);
    this->runAction(seq);
    
    auto rand = CCRANDOM_0_1();
    if (rand > 0.6)
    {
        log("Extra Power created: %f", rand);
        ExtraPower* powerUp;
        if (rand <= 0.75) {
            powerUp = ExtraPower::createWithType('p');
        } else {
            if (rand < 0.9) {
                powerUp = ExtraPower::createWithType('e');
            } else {
                powerUp = ExtraPower::createWithType('c');
            }
        }
        powerUp->setPosition(getPosition());
        getParent()->addChild(powerUp);
    }
}

bool Brick::init(cocos2d::Vec2 pos, int value)
{
    value %= metadata.size();
    initWithSpriteFrameName(metadata.at(value).frame);
    setTag(TAG_BRICK);
    setPosition(Vec2(pos.x * _contentSize.width, pos.y * _contentSize.height));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    BrickData *data = new BrickData();
    data->value = metadata.at(value).value;
    data->hits = metadata.at(value).hits;
    setUserData(data);
    
    auto pb = PhysicsBody::createBox(_contentSize,  PhysicsMaterial(0.1f, 1.0f, 0.0f));
    pb->setDynamic(false);
    pb->setGravityEnable(false);
    pb->setCategoryBitmask(0x02);    // 0010
    pb->setContactTestBitmask(0x01); // 1000
    pb->setCollisionBitmask(0x01);   // 0001
    addComponent(pb);

    _size0 = getContentSize();
    
    return true;
}

void Brick::updateImage()
{
//    auto *data = static_cast<Brick::BrickData *>(getUserData());
//    this->setSpriteFrame(data->frame);
}

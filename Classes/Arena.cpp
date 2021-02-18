//
//  Arena.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/13/21.
//

#include "Arena.h"

USING_NS_CC;

Arena::Arena() :
numXTiles(12),
numYTiles(14),
tileSize(31)
{
}

Arena* Arena::create(int tileNum)
{
    Arena *pRet = new(std::nothrow) Arena();
    if (pRet && pRet->init(tileNum))
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

// on "init" you need to initialize your instance
bool Arena::init(int tileNum)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    makeBackground(tileNum);
    return true;
}

Arena::~Arena()
{
}

void Arena::makeBackground(int tilenum)
{
    for (int x = 0; x < 14; x++) {
        auto border = drawTile(borderNames[bordertop[x]], x, numYTiles);
        auto pb = PhysicsBody::createBox(border->getContentSize() , PhysicsMaterial(0.1f, 1, 0.0f));
        pb->setGravityEnable(false);
        pb->setCategoryBitmask(0x08);    // 1000
        pb->setContactTestBitmask(0x01); // 0111
        pb->setCollisionBitmask(0x01);   // 0001
        pb->setDynamic(false);
        border->addComponent(pb);
    }
    for (int y = 0; y < 14; y++) {
        auto border = drawTile(borderNames[borderleft[y]], 0, y);
        auto pb = PhysicsBody::createBox(border->getContentSize() + Size(0,2), PhysicsMaterial(0.1f, 1, 0.0f));
        pb->setGravityEnable(false);
        pb->setCategoryBitmask(0x08);    // 1000
        pb->setContactTestBitmask(0x01); // 0010
        pb->setCollisionBitmask(0x01);   // 0001
        pb->setDynamic(false);
        border->addComponent(pb);

        border = drawTile(borderNames[borderright[y]], numXTiles + 1, y);
        pb = PhysicsBody::createBox(border->getContentSize() + Size(0,2),  PhysicsMaterial(0.1f, 1, 0.0f));
        pb->setGravityEnable(false);
        pb->setCategoryBitmask(0x08);    // 1000
        pb->setContactTestBitmask(0x01); // 0010
        pb->setCollisionBitmask(0x01);   // 0001
        pb->setDynamic(false);
        border->addComponent(pb);
    }
    for(int x = 0; x < numXTiles; x++) {
        for (int y = 0; y < numYTiles; y++) {
            drawTile(tiles[tilenum], x + 1, y );
        }
    }
}

Sprite* Arena::drawTile(std::string frameName, int x, int y)
{
    auto sprite = Sprite::createWithSpriteFrameName(frameName);
    sprite->setPosition(Vec2(x * tileSize, tileSize * y));
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addChild(sprite);
    return sprite;
}

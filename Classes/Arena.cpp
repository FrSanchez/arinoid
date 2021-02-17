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
    borders = new (std::nothrow) Rect[] {
//# left border - 0, right border - 1,
//    # special left border - 2, special right border - 3
        {129, 257, 31, 31},
        {193, 257, 31, 31},
        {129, 225, 31, 31},
        {193, 225, 31, 31},
//# plain border - 4, special border - 5, upper left - 6, upper right - 7
        {449,  36, 31, 10},
        {129, 290, 31, 13},
        {129, 193, 31, 13},
        {193, 193, 31, 13}
    };
    
    tiles = new (std::nothrow) Rect[] {
        {129, 321, 31, 30},//,   # purple - 0
        {161, 321, 31, 31},//,   # dark blue - 1
        {129, 353, 31, 31},//,   # red - 2
        {161, 353, 31, 31},//,   # green - 3
        {129, 385, 31, 31} //    # blue - 4
    };
}

// on "init" you need to initialize your instance
bool Arena::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    makeBackground(4);
    return true;
}

Arena::~Arena()
{
    delete[] borders;
}

void Arena::makeBackground(int tilenum)
{
    int bordertop[] = {6, 4, 4, 4, 5, 4, 4, 4, 4, 5, 4, 4, 4, 7};
    int borderleft[] = {0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0};
    int borderright[] = {1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1};
    
    for (int x = 0; x < 14; x++) {
        auto border = drawTile(borders[bordertop[x]], x, numYTiles);
        auto pb = PhysicsBody::createBox(borders[bordertop[x]].size);
        pb->setGravityEnable(false);
        pb->setCategoryBitmask(0x01);    // 0001
        pb->setContactTestBitmask(0xff); // 1000
        pb->setCollisionBitmask(0xff);   // 0001
        pb->setDynamic(false);
        border->addComponent(pb);
    }
    for (int y = 0; y < 14; y++) {
        auto border = drawTile(borders[borderleft[y]], 0, y);
        auto pb = PhysicsBody::createBox(borders[borderleft[y]].size);
        pb->setGravityEnable(false);
        pb->setCategoryBitmask(0x01);    // 0001
        pb->setContactTestBitmask(0xff); // 1000
        pb->setCollisionBitmask(0xff);   // 0001
        pb->setDynamic(false);
        border->addComponent(pb);

        border = drawTile(borders[borderright[y]], numXTiles + 1, y);
        pb = PhysicsBody::createBox(borders[borderright[y]].size);
        pb->setGravityEnable(false);
        pb->setCategoryBitmask(0x01);    // 0001
        pb->setContactTestBitmask(0xff); // 1000
        pb->setCollisionBitmask(0xff);   // 0001
        pb->setDynamic(false);
        border->addComponent(pb);
    }
    for(int x = 0; x < numXTiles; x++) {
        for (int y = 0; y < numYTiles; y++) {
            drawTile(tiles[tilenum], x + 1, y );
        }
    }
}

Sprite* Arena::drawTile(Rect imageRect, int x, int y)
{
    auto sprite = Sprite::create("arinoid_master.png", imageRect);
    sprite->setPosition(Vec2(topx + x * tileSize, topy + tileSize * y));
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addChild(sprite);
    return sprite;
}

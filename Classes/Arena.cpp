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

// on "init" you need to initialize your instance
bool Arena::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    borders = new (std::nothrow) Rect[8];
    
    borders[0] = Rect(129, 257, 31, 31);
    borders[1] = Rect(193, 257, 31, 31);
    borders[2] = Rect(129, 225, 31, 31);
    borders[3] = Rect(193, 225, 31, 31);

    borders[4] = Rect(449,  36, 31, 10);
    borders[5] = Rect(129, 290, 31, 13);
    borders[6] = Rect(129, 193, 31, 13);
    borders[7] = Rect(193, 193, 31, 13);

    tiles = new (std::nothrow) Rect[5];
    
    tiles[0] = Rect(129, 321, 31, 30);//,   # purple - 0
    tiles[1] = Rect(161, 321, 31, 31);//,   # dark blue - 1
    tiles[2] = Rect(129, 353, 31, 31);//,   # red - 2
    tiles[3] = Rect(161, 353, 31, 31);//,   # green - 3
    tiles[4] = Rect(129, 385, 31, 31);//    # blue - 4

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
        drawTile(borders[bordertop[x]], x, numYTiles);
    }
    for (int y = 0; y < 14; y++) {
        drawTile(borders[borderleft[y]], 0, y);
        drawTile(borders[borderright[y]], numXTiles + 1, y);
    }
    for(int x = 0; x < numXTiles; x++) {
        for (int y = 0; y < numYTiles; y++) {
            drawTile(tiles[tilenum], x + 1, y );
        }
    }
}

void Arena::drawTile(Rect image, int x, int y)
{
    auto sprite = Sprite::create("arinoid_master.png", image);
    sprite->setPosition(Vec2(topx + x * tileSize, topy + tileSize * y));
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    addChild(sprite);
}

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
numYTiles(14)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("tile");
    tileSize = frame->getOriginalSize().width;
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

void Arena::setTile(int tileNum)
{
//    tileNum %= MAX_NUM_TILES;
    auto color = Color3B(random(0, 255), random(0, 255), random(0, 255));
    auto children = getChildByTag(0x88)->getChildren();
    auto tintTo = TintTo::create(tileNum, random(0, 255), random(0, 255), random(0, 255));
    for (auto iter : children){
        Sprite* sprite = dynamic_cast<Sprite *>(iter);
        if (sprite && sprite->getTag() == 0x11) {
            sprite->runAction(tintTo->clone());
        }
    }
    scheduleOnce([&](float dt){ setTile(10);}, 10, "recolor");
}

// on "init" you need to initialize your instance
bool Arena::init(int tileNum)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    setTag(ARENA_TAG);
    makeBackground(tileNum);
    setContentSize(Size((1 + numXTiles) * tileSize, ( 1 + numYTiles) * tileSize));
    return true;
}

Arena::~Arena()
{
}

void Arena::makeBackground(int tilenum)
{
//    for (int x = 0; x < 14; x++) {
//        auto border = drawTile(borderNames[bordertop[x]], x, numYTiles);
//    }
//    for (int y = 0; y < 14; y++) {
//        auto border = drawTile(borderNames[borderleft[y]], 0, y);
//        border = drawTile(borderNames[borderright[y]], numXTiles + 1, y);
//    }
    Node* root = Node::create();
    root->setTag(0x88);
    addChild(root);
    for(int x = 0; x < numXTiles; x++) {
        for (int y = 0; y < numYTiles; y++) {
            auto tile = drawTile("", x + 1, y );
            tile->setTag(0x11);
            root->addChild(tile);
        }
    }
    
    auto pb = PhysicsBody::create();
    PhysicsMaterial mat(PHYSICS_INFINITY, 1, 0.0f);
    pb->addShape(PhysicsShapeBox::create(Size(tileSize,  (numYTiles + 1) * tileSize), mat, Vec2(((numXTiles + 1) * tileSize) / 2 , 0)));
    pb->addShape(PhysicsShapeBox::create(Size(tileSize,  (numYTiles + 1) * tileSize), mat, Vec2(((-numXTiles - 1) * tileSize) /2, 0)));
    pb->addShape(PhysicsShapeBox::create(Size( (numXTiles + 1) * tileSize + 4,  tileSize), mat, Vec2(0, numYTiles / 2 * tileSize + tileSize)));
    pb->setPositionOffset(Vec2((1 + numXTiles) * tileSize / 2 , ( numYTiles) * tileSize / 2 ));
    pb->setGravityEnable(false);
    pb->setCategoryBitmask(0x08);    // 1000
    pb->setContactTestBitmask(0x11); // 0001
    pb->setCollisionBitmask(0x11);   // 0001
    pb->setDynamic(false);
    addComponent(pb);
    
    _arenaRect = Rect(0, 0, numXTiles * tileSize, numYTiles * tileSize);
}

Sprite* Arena::drawTile(std::string frameName, int x, int y)
{
    auto sprite = Sprite::createWithSpriteFrameName("tile");
    sprite->setPosition(Vec2(x * tileSize, tileSize * y));
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    return sprite;
}

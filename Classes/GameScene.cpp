//
//  GameScene.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/11/21.
//

#include "GameScene.h"
#include "SplashScene.h"

USING_NS_CC;

std::string itoa(int value, int base);

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    
    _level = 2;
    _score = 0;
//    _physicsWorld->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto title = Sprite::createWithSpriteFrameName("smallTitle");
    title->setPosition(Vec2(size.width / 2, size.height - 64));
    title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(title);
    
    auto arena = Arena::create(4);
    arena->setPosition(Vec2(0, 96));
    arena->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(arena);
        
    auto score = Sprite::createWithSpriteFrameName("score");
    score->setPosition(Vec2(size.width / 2, size.height - 128));
    score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(score);
    
    auto scoreLbl = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 18);
    scoreLbl->setTextColor(Color4B(252, 217, 197, 255));
    scoreLbl->setTag(0x22);
    auto pos = score->getPosition();
    pos.x += score->getContentSize().width / 2 + 16;
    scoreLbl->setPosition(pos);
    addChild(scoreLbl);
    
    _paddle = Paddle::create();
    arena->addChild(_paddle);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    makeLevel(arena, _level);
    
    _ball = Ball::create();
    arena->addChild(_ball);
    
    schedule(CC_SCHEDULE_SELECTOR(GameScene::tick));
    
    _livesSprites.empty();
    for(int i = 0; i < _lives; i++)
    {
        auto sprite = Sprite::createWithSpriteFrameName("paddle");
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        sprite->setScale(0.4);
        sprite->setPosition(Vec2(sprite->getContentSize().width / 2 * i + 16, 64));
        addChild(sprite);
        _livesSprites.pushBack(sprite);
    }

    initRound();
    
    return true;
}

void GameScene::endScene(float dt)
{
    auto scene = SplashScene::create();
    auto fade = TransitionProgressOutIn::create(1, scene);
    Director::getInstance()->replaceScene(fade);
}

void GameScene::initRound()
{
    auto size = Director::getInstance()->getVisibleSize();
    
    _paddle->setPosition(Vec2(size.width / 2, 32));
    _ball->setPosition(128, 128);
    _ball->getPhysicsBody()->setVelocity(Vec2::ZERO);
    _ball->setVisible(false);

    log("Remaining lives: %d" , _lives);
    
    if (_lives <= 0) {
        auto gameOver = Sprite::createWithSpriteFrameName("gameOver");
        gameOver->setPosition(Vec2(size.width / 2, size.height / 2 - 92));
        addChild(gameOver);
        scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::endScene), 2);
        return;
    }
    auto str = StringUtils::format("ROUUND  %d", _level);
    auto roundLbl = Label::createWithTTF(str.c_str(), "fonts/Marker Felt.ttf", 32);
    addChild(roundLbl);
    roundLbl->setPosition(Vec2(size.width / 2, size.height / 2 - 92));
    roundLbl->setTextColor(Color4B(252, 217, 197, 255));
    
    auto getReady = Sprite::createWithSpriteFrameName("getReady");//(SPRITESHEET, Rect(201, 361, 167 , 17));
    getReady->setPosition(Vec2(size.width / 2, size.height / 2 - 124));
    addChild(getReady);

    scheduleOnce([=](float dt){
        int x = cocos2d::random(0, 10) > 5 ? 100 : -100;
        _ball->getPhysicsBody()->setVelocity(Vec2(x, 100));
        roundLbl->removeFromParentAndCleanup(true);
        getReady->removeFromParentAndCleanup(true);
        if (_livesSprites.size() > 0) {
            Sprite* sprite = _livesSprites.at(_livesSprites.size() - 1);
            sprite->removeFromParentAndCleanup(true);
            _livesSprites.popBack();
        }
        _paddle->start();
        _ball->setVisible(true);
    }, 2, "start");
}

void GameScene::die()
{
    _ball->setPosition(128, 128);
    _ball->getPhysicsBody()->setVelocity(Vec2::ZERO);
    _ball->setVisible(false);
    _paddle->die( CC_CALLBACK_0(GameScene::initRound, this));
    _lives--;
}

void GameScene::tick(float dt)
{
    if (_ball && _ball->getPosition().y < 0) {
        die();
    }
}

void GameScene::makeLevel(Arena* arena, int level)
{
    level--;
    for (int y = 0; y < 24; y++) {
        for(int x = 0; x < 12; x++) {
            if (levels[level][y][x] > 0) {
                auto brick = Brick::create(Vec2(x + 1, y + 4), levels[level][y][x]);
                arena->addChild(brick);
            }
        }
    }
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    Brick* brick = static_cast<Brick*>( (a->getNode()->getTag() == TAG_BRICK) ? a->getNode() : b->getNode() );
    if (brick->getTag() == TAG_BRICK) {
        auto *data = static_cast<Brick::BrickData *>(brick->getUserData());
        if (data->hits > 0) {
            data->hits--;
            brick->updateImage();
        } else {
            addToScore(data->value);
            brick->removeFromParentAndCleanup(true);
            CC_SAFE_DELETE(data);
        }
    }
    
    return true;
}

void GameScene::addToScore(int value)
{
    _score += value;
    Label* scoreLbl = static_cast<Label*>(getChildByTag(0x22));
    if (scoreLbl) {
        auto str = StringUtils::format("%d", _score);
        scoreLbl->setString(str.c_str());
    }
}
//
///**
//     * C++ version 0.4 std::string style "itoa":
//     * Contributions from Stuart Lowe, Ray-Yuan Sheu,
//
//     * Rodrigo de Salvo Braz, Luc Gallant, John Maloney
//     * and Brian Hunt
//     */
//std::string itoa(int value, int base) {
//
//    std::string buf;
//
//    // check that the base if valid
//    if (base < 2 || base > 16) return buf;
//
//    enum { kMaxDigits = 35 };
//    buf.reserve( kMaxDigits ); // Pre-allocate enough space.
//
//
//    int quotient = value;
//
//    // Translating number to string with base:
//    do {
//        buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
//        quotient /= base;
//    } while ( quotient );
//
//    // Append the negative sign
//    if ( value < 0) buf += '-';
//
//    std::reverse( buf.begin(), buf.end() );
//    return buf;
//}
//

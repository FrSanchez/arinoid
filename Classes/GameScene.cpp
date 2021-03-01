//
//  GameScene.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/11/21.
//

#include "GameScene.h"
#include "SplashScene.h"

USING_NS_CC;
#define GAME_FONT "fonts/font1.fnt"

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

    _level = 1;
    _gainLevelThreshold = 1;
    _lives = 3;
//    _physicsWorld->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto title = Sprite::createWithSpriteFrameName("title-small");
    title->setPosition(Vec2(size.width / 2, size.height - 64));
    title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(title);
    
    auto *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("tile");
    initialVelocity = frame->getOriginalSize().width * 5;
    
    auto arena = Arena::create(_level);
    arena->setPosition(Vec2(size.width / 2 + 0, size.height / 2));
    arena->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(arena);
        
    auto score = Label::createWithBMFont(GAME_FONT, "SCORE: 0");
    score->setPosition(Vec2(size.width / 2, size.height - score->getContentSize().height / 2));
    score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    score->setTag(0x22);
    addChild(score);
        
    _paddle = Paddle::create();
    _paddle->setArenaWidth(arena->getContentSize().width);
    arena->addChild(_paddle);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
// Togle debug
    MenuItemFont::setFontSize(64);
    auto item = MenuItemFont::create("Toggle debug", [&](Ref* pSender) {
        _debugDraw = !_debugDraw;
        _physicsWorld->setDebugDrawMask(_debugDraw ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);
    });
    
    auto menu = Menu::create(item, nullptr);
    this->addChild(menu);
    menu->setPosition(Vec2(size.width - item->getContentSize().width / 2 - 10, size.height - item->getContentSize().height / 2 - 10));
// toggle debug end
    
// cheat level begin
    item = MenuItemFont::create("next Level", [&](Ref* pSender) {
        winLevel();
    });
    
    menu = Menu::create(item, nullptr);
    this->addChild(menu);
    menu->setPosition(Vec2(item->getContentSize().width / 2 + 10, size.height - item->getContentSize().height / 2 - 10));
// cheat level end
    
    _level = 1;
    initLevel();
    
    ExtraPower::callbacksMap.clear();
    ExtraPower::callbacksMap['e'] = CC_CALLBACK_0(Paddle::powerUpGrow, _paddle);
    ExtraPower::callbacksMap['p'] = CC_CALLBACK_0(Paddle::powerUpShrink, _paddle);
    ExtraPower::callbacksMap['c'] = CC_CALLBACK_0(GameScene::extraBallsPowerUp, this);
    return true;
}

void GameScene::extraBallsPowerUp()
{
    auto _ball = getChildByTag(ARENA_TAG)->getChildByTag(BALL_TAG);
    float angle = 60;
    for (int i =0 ; i< 3; i++) {
        auto ball = addBall();
        ball->setPosition(_ball->getPosition());
        angle+=60;
    }
}

Ball* GameScene::addBall()
{
    auto ball = Ball::create();
    auto arena = getChildByTag(ARENA_TAG);
    int x = cocos2d::random(0, 10) > 5 ? initialVelocity : -initialVelocity;
    ball->getPhysicsBody()->setVelocity(Vec2(x, initialVelocity));
    ball->setOnLostBall(CC_CALLBACK_1(GameScene::loseBall, this));
    arena->addChild(ball);
    _ballCount++;
    log("New ball now %d speed %f", _ballCount, ball->getPhysicsBody()->getVelocity().length());

    return ball;
}

Node* GameScene::createShadow(Vec2 pos, Color4F color, Size size)
{
    auto draw = DrawNode::create();
    draw->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    draw->setPosition(pos);

    draw->drawSolidCircle(Vec2::ZERO, size.width / 2 , CC_DEGREES_TO_RADIANS(90), 20, 0.5f, 0.5f, color);
    draw->setOpacity(128);
    auto seq = Sequence::create(FadeOut::create(0.15), CallFunc::create([&, draw](){
        draw->removeFromParentAndCleanup(true);
    }), nullptr);
    draw->runAction(seq);
    return draw;
//    draw->scheduleOnce([&](float dt) {
//    }, 1, "won");
}

void GameScene::initLevel()
{
    auto arena = static_cast<Arena*>(getChildByTag(ARENA_TAG));
    makeLevel(arena, _level);
    _score = 0;

    _livesSprites.empty();
    Node* sprite;
    do {
        sprite = getChildByTag(0x1e);
        if (sprite) {
            sprite->removeFromParentAndCleanup(true);
        }
    } while (sprite);
    
    for(int i = 0; i < _lives; i++)
    {
        addLifeSprite(i);
    }
    initRound();
}

Sprite* GameScene::addLifeSprite(int pos)
{
    auto sprite = Sprite::createWithSpriteFrameName("paddleLife");
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    sprite->setTag(0x1e);
    addChild(sprite);
    _livesSprites.pushBack(sprite);
    sprite->setPosition(Vec2(sprite->getContentSize().width * pos * 1.2, sprite->getContentSize().height ));
    return sprite;

}

void GameScene::endScene(float dt)
{
    AudioEngine::stopAll();
    auto scene = SplashScene::create();
    auto fade = TransitionProgressOutIn::create(1, scene);
    Director::getInstance()->replaceScene(fade);
}

void GameScene::removeBalls()
{
    _ballCount = 0;

    Node* ball =nullptr;
    do {
        ball = getChildByTag(ARENA_TAG)->getChildByTag(BALL_TAG);
        if (nullptr != ball) {
            ball->removeFromParentAndCleanup(true);
        }
    } while (ball != nullptr);

}

void GameScene::initRound()
{
    auto size = Director::getInstance()->getVisibleSize();

    removeBalls();
    
    _paddle->setPosition(Vec2(size.width / 2, 64));

    if (_lives <= 0) {
        auto gameOver = Label::createWithBMFont(GAME_FONT, "GAME OVER!");
        gameOver->setPosition(Vec2(size.width / 2, size.height / 2 - 92));
        addChild(gameOver);
        scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::endScene), 2);
        return;
    }
    auto str = StringUtils::format("ROUND %d", _level);
    
    auto roundLbl = Label::createWithBMFont(GAME_FONT, str.c_str());
    addChild(roundLbl);
    roundLbl->setPosition(Vec2(size.width / 2, size.height / 2 - 92));

    
    auto getReady = Label::createWithBMFont(GAME_FONT, "GET READY!");
    getReady->setPosition(Vec2(size.width / 2, roundLbl->getPosition().y - roundLbl->getContentSize().height * 2));
    addChild(getReady);

    scheduleOnce([=](float dt){
        auto _ball = addBall();
        _ball->setPosition(_paddle->getPosition());
        roundLbl->removeFromParentAndCleanup(true);
        getReady->removeFromParentAndCleanup(true);
        if (_livesSprites.size() > 0) {
            Sprite* sprite = _livesSprites.at(_livesSprites.size() - 1);
            sprite->removeFromParentAndCleanup(true);
            _livesSprites.popBack();
        }
        _paddle->start();
        _ball->setVisible(true);
        // melodyloops-preview-your-optimistic-future-2m30s.mp3
        AudioEngine::play2d("loop.mp3", true, 0.5f);
    }, 2, "start");
}

void GameScene::die()
{
    AudioEngine::stopAll();
    AudioEngine::play2d("10.mp3", false, 1.0f);
    _ballCount = 0;
//    _ball->setPosition(128, 128);
//    _ball->getPhysicsBody()->setVelocity(Vec2::ZERO);
//    _ball->setVisible(false);
    _paddle->die( CC_CALLBACK_0(GameScene::initRound, this));
    _lives--;
}

void GameScene::makeLevel(Arena* arena, int level)
{
    _brickCount = 0;
    level--;
    _brickCount = 0;
    Node* brick = nullptr;
    do {
        brick = arena->getChildByTag(TAG_BRICK);
        if (brick) {
            brick->removeFromParentAndCleanup(true);
        }
    } while(brick);
    
    arena->setTile(0);
    for (int y = 0; y < 24; y++) {
        for(int x = 0; x < 12; x++) {
            if (levels[level][y][x] > 0) {
                auto brick = Brick::create(Vec2(x + 1, y + 4), levels[level][y][x] - 1);
                if (brick) {
                    arena->addChild(brick);
                    auto *data = static_cast<Brick::BrickData *>(brick->getUserData());
                    if (data->value > 0) {
                        _brickCount++;
                    }
                }
            }
        }
    }
}

void GameScene::winLevel()
{
    removeBalls();
    _paddle->setVisible(false);

    AudioEngine::stopAll();
    _level++;
    if (_level > maxLevel) {
        endScene(0);
        return;
    }
    
    Node* powerUp = nullptr;
    do {
        powerUp = getChildByTag(ARENA_TAG)->getChildByTag(POWERUP_TAG);
        if (nullptr != powerUp) {
            powerUp->removeFromParentAndCleanup(true);
        }
    } while(powerUp != nullptr);

    AudioEngine::play2d("9.mp3", false, 1.0);
    scheduleOnce([&](float dt) {
        this->initLevel();
    }, 1, "won");
}

Node* GameScene::getContact(PhysicsBody *a, PhysicsBody *b, int tag)
{
    auto aNode = a->getNode();
    auto bNode = b->getNode();
    if (aNode != nullptr && aNode->getTag() == tag) {
        return aNode;
    }
    if (bNode != nullptr && bNode->getTag() == tag) {
        return bNode;
    }
    return nullptr;
}

void GameScene::loseBall(Ball* ball)
{
    _ballCount--;
    ball->removeFromParentAndCleanup(true);
    if (_ballCount <= 0) {
        die();
    }
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    AudioEngine::play2d("1.mp3", false, 1.0f);
    Ball* ball = static_cast<Ball*>(getContact(a, b, BALL_TAG) );
    Arena* arena = static_cast<Arena*>(getContact(a, b, ARENA_TAG) );
    Brick* brick = static_cast<Brick*>( getContact(a, b, TAG_BRICK) );
    ExtraPower* power = static_cast<ExtraPower*>( getContact(a, b, POWERUP_TAG));
    Paddle* paddle = static_cast<Paddle*>( getContact(a, b, PADDLE_TAG));
    
    log("contact %s %s", itoa(a->getCategoryBitmask(), 2).c_str(), itoa(b->getCategoryBitmask(), 2).c_str());
    
    if (ball) {
        log("%f %f", ball->getPhysicsBody()->getMoment(), ball->getPhysicsBody()->getVelocity().length());
        if (arena) {
            
            if (ball->getPosition().y < _paddle->getPosition().y - _paddle->getContentSize().height
                            && ball->getPhysicsBody()->getVelocity().y < 0) {
                loseBall(ball);
            }
        }
        if (paddle) {
            paddle->hitBall(ball);
        }
    }
    
    if (power != nullptr)
    {
        if (arena != nullptr) {
            power->die();
        }
        if (paddle != nullptr) {
            power->caught();
        }
    }
    
    if (brick) {
        auto *data = static_cast<Brick::BrickData *>(brick->getUserData());
        if (data->hits > 0) {
            brick->updateImage();
            data->hits--;
            brick->hit();
        } else {
            addToScore(data->value);
            brick->remove();
            CC_SAFE_DELETE(data);
            _brickCount--;
            if (_brickCount <= 0) {
                scheduleOnce([&](float dt){
                    winLevel();
                }, 0, "winLevel");
            }
        }
    }
    
    
    return true;
}

int GameScene::getGainThreshold()
{
    return _gainLevelThreshold * 10000;
}

void GameScene::addToScore(int value)
{
    _score += value;
    if (_score > getGainThreshold()) {
        _gainLevelThreshold++;
        AudioEngine::play2d("5.mp3", false, 1.0f);
        addLifeSprite(MAX(0, _lives - 1));
        _lives++;
        log("Lives: %d threshold: %d", _lives, _gainLevelThreshold);
    }
    Label* scoreLbl = static_cast<Label*>(getChildByTag(0x22));
    if (scoreLbl) {
        auto str = StringUtils::format("SCORE: %d", _score);
        scoreLbl->setString(str.c_str());
    }
}

/**
     * C++ version 0.4 std::string style "itoa":
     * Contributions from Stuart Lowe, Ray-Yuan Sheu,

     * Rodrigo de Salvo Braz, Luc Gallant, John Maloney
     * and Brian Hunt
     */
std::string itoa(int value, int base) {

    std::string buf;

    // check that the base if valid
    if (base < 2 || base > 16) return buf;

    enum { kMaxDigits = 35 };
    buf.reserve( kMaxDigits ); // Pre-allocate enough space.


    int quotient = value;

    // Translating number to string with base:
    do {
        buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
        quotient /= base;
    } while ( quotient );

    // Append the negative sign
    if ( value < 0) buf += '-';

    std::reverse( buf.begin(), buf.end() );
    return buf;
}


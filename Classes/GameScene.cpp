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
    _gainLevelThreshold = 1000;
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
    score->setPosition(Vec2(size.width / 2, size.height - 128));
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
    
    _ball = Ball::create();
    arena->addChild(_ball);
    schedule([&, arena](float dt){
        if (_ball->isVisible()) {
            auto shadow = createShadow(_ball->getPosition(), Color4F::GRAY);
            arena->addChild(shadow);
        }
    }, "streakUpdate");
    _level = 1;
    initLevel();
    
    return true;
}

Node* GameScene::createShadow(Vec2 pos, Color4F color)
{
    auto draw = DrawNode::create();
    draw->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    draw->setPosition(pos);
    // draw a rectangle

    draw->drawSolidCircle(Vec2::ZERO, _ball->getContentSize().width , CC_DEGREES_TO_RADIANS(90), 20, 0.5f, 0.5f, color);
    draw->setOpacity(128);
    auto seq = Sequence::create(FadeOut::create(0.1), CallFunc::create([&, draw](){
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
        auto sprite = Sprite::createWithSpriteFrameName("paddleLife");
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        sprite->setTag(0x1e);
        sprite->setPosition(Vec2(sprite->getContentSize().width * i * 1.2, 64));
        addChild(sprite);
        _livesSprites.pushBack(sprite);
    }
    initRound();
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
    
    _paddle->setPosition(Vec2(size.width / 2, _ball->getContentSize().height * 2));
    _ball->getPhysicsBody()->setVelocity(Vec2::ZERO);
    _ball->setVisible(false);

    log("Remaining lives: %d" , _lives);
    
    if (_lives <= 0) {
//        auto gameOver = Sprite::createWithSpriteFrameName("gameOver");
        auto gameOver = Label::createWithBMFont(GAME_FONT, "GAME OVER!");
        gameOver->setPosition(Vec2(size.width / 2, size.height / 2 - 92));
        addChild(gameOver);
        scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::endScene), 2);
        return;
    }
    auto str = StringUtils::format("ROUND  %d", _level);
//    auto roundLbl = Label::createWithTTF(str.c_str(), "fonts/Marker Felt.ttf", 32);
    auto roundLbl = Label::createWithBMFont(GAME_FONT, str.c_str());
    addChild(roundLbl);
    roundLbl->setPosition(Vec2(size.width / 2, size.height / 2 - 92));
//    roundLbl->setTextColor(Color4B(252, 217, 197, 255));
    
    
//    auto getReady = Sprite::createWithSpriteFrameName("getReady");//(SPRITESHEET, Rect(201, 361, 167 , 17));
    auto getReady = Label::createWithBMFont(GAME_FONT, "GET READY!");
    getReady->setPosition(Vec2(size.width / 2, size.height / 2 - 124));
    addChild(getReady);

    scheduleOnce([=](float dt){
        int x = cocos2d::random(0, 10) > 5 ? initialVelocity : -initialVelocity;
        _ball->setPosition(_paddle->getPosition());
        _ball->getPhysicsBody()->setVelocity(Vec2(x, initialVelocity));
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
    AudioEngine::play2d("10.mp3", false, 1.0f);
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
    
    arena->setTile(level);
    for (int y = 0; y < 24; y++) {
        for(int x = 0; x < 12; x++) {
            if (levels[level][y][x] > 0) {
                auto brick = Brick::create(Vec2(x + 1, y + 4), levels[level][y][x]);
                if (brick) {
                    arena->addChild(brick);
                    _brickCount++;
                }
            }
        }
    }
}

void GameScene::winLevel()
{
    _level++;
    if (_level > maxLevel) {
        endScene(0);
        return;
    }
    AudioEngine::play2d("9.mp3", false, 1.0);
    _ball->setPosition(128, 128);
    _ball->getPhysicsBody()->setVelocity(Vec2::ZERO);
    _ball->setVisible(false);
    _paddle->setVisible(false);
    scheduleOnce([&](float dt) {
        this->initLevel();
    }, 1, "won");
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    AudioEngine::play2d("1.mp3", false, 1.0f);
    CCLOG("%s %s", itoa(a->getCategoryBitmask(), 2).c_str(), itoa(b->getCategoryBitmask(), 2).c_str());
    Ball* ball = static_cast<Ball*>( (a->getCategoryBitmask() == 0x01) ? a->getNode() : b->getNode() );
    Arena* arena = static_cast<Arena*>( (a->getNode()->getTag() == ARENA_TAG) ? a->getNode() : b->getNode() );
    Brick* brick = static_cast<Brick*>( (a->getNode()->getTag() == TAG_BRICK) ? a->getNode() : b->getNode() );
    
    if (ball->getTag() == BALL_TAG && arena->getTag() == ARENA_TAG ) {
//        CCLOG("pos %f, %f  , vel %f, %f", ball->getPosition().x, ball->getPosition().y, ball->getPhysicsBody()->getVelocity().x, ball->getPhysicsBody()->getVelocity().y);
        // find if hit the bottom wall, by checing velocity y is negative and if the ball is lower than the paddle
        if (_ball->getPosition().y < _paddle->getPosition().y - _paddle->getContentSize().height
            && _ball->getPhysicsBody()->getVelocity().y < 0) {
            die();
        }
    }
    
    if (brick->getTag() == TAG_BRICK) {
        auto *data = static_cast<Brick::BrickData *>(brick->getUserData());
        if (data->hits > 0) {
            data->hits--;
            brick->updateImage();
        } else {
            addToScore(data->value);
            brick->remove();
            CC_SAFE_DELETE(data);
            _brickCount--;
            if (_brickCount <= 0) {
                winLevel();
            }
        }
    }
    
    
    return true;
}

void GameScene::addToScore(int value)
{
    _score += value;
    if (_score > _gainLevelThreshold) {
        _lives++;
        _gainLevelThreshold *= 1.1;
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


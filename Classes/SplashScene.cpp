//
//  SplashScene.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/17/21.
//

#include "SplashScene.h"
#include "GameScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SplashSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto size = Director::getInstance()->getVisibleSize();

//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("arinoid.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spritesheet.plist");

    auto icon = Sprite::createWithSpriteFrameName("arinoid");
    icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    icon->setTag(2);
    icon->setPosition(Vec2(size.width/ 2, size.height/ 2));
    icon->setOpacity(0);
    icon->runAction( FadeIn::create(2));
    addChild(icon);

    LoadingBar* loadingBar = LoadingBar::create("sliderProgress.png");
    addChild(loadingBar);
    loadingBar->setTag(1);
    loadingBar->setPosition(Vec2(size.width / 2.0f, size.height / 4.0f ));
    loadingBar->setDirection(LoadingBar::Direction::LEFT);
    loadingBar->setPercent(1);
    loadingBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::doProgress), 0);
    
    schedule([&, loadingBar](float dt) {
        static float pct = 0;
        pct+= 25*dt;
        loadingBar->setPercent(pct);
    }, 0, "pct");
    
    return true;
}

void SplashScene::doProgress(float dt)
{
    // first cache sounds
    for(int num = 1 ; num <= 12; num++)
    {
        auto name = StringUtils::format("%d.mp3", num);
        AudioEngine::preload(name.c_str());
        num++;
    }
    AudioEngine::preload("loop.mp3");
    
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto icon = static_cast<Sprite*>(getChildByTag(2));
    removeChild(icon, true);
    
    icon = Sprite::createWithSpriteFrameName("arinoid");
    icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    icon->setPosition(Vec2::ZERO);

    auto startItem = MenuItemSprite::create(icon, icon, [=](Ref* pSender){
        auto scene = GameScene::create();
        auto fade = TransitionFade::create(0.5, scene);
        Director::getInstance()->replaceScene(fade);
    });
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(size.width/2, size.height/2));
    menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(menu);
    
 
    auto closeItem = MenuItemImage::create(
                                           "exit.png",
                                           "exit_pressed.png",
                                           CC_CALLBACK_1(SplashScene::menuCloseCallback, this));

   
    float x = origin.x + size.width - closeItem->getContentSize().width/2;
    float y = origin.y + closeItem->getContentSize().height/2;
    closeItem->setPosition(Vec2(x,y));

    // create menu, it's an autorelease object
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //  Create a "one by one" touch event listener
    // (processes one touch at a time)
    auto listener1 = EventListenerTouchOneByOne::create();

    // trigger when you push down
    listener1->onTouchBegan = [=](Touch* touch, Event* event){
        // your code
        auto node = createSpinnyNode(touch->getLocation(), Color4F::GREEN);
        addChild(node);
        return true; // if you are consuming it
    };

    Director::getInstance()->getTextureCache()->addImage("stars.png") ;
    // trigger when moving touch
    listener1->onTouchMoved = [=](Touch* touch, Event* event){
        // your code
        auto node = createSpinnyNode(touch->getLocation(), Color4F::BLUE);
        addChild(node);
    };

    // trigger when you let up
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
        auto node = createSpinnyNode(touch->getLocation(), Color4F::RED);
        addChild(node);
    };

    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    getChildByTag(1)->removeFromParentAndCleanup(true);
    this->unscheduleAllCallbacks();

}

Node* SplashScene::createSpinnyNode(Vec2 pos, Color4F color)
{
    auto draw = DrawNode::create();
    draw->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    draw->setPosition(pos);
    // draw a rectangle

    draw->drawRect(Vec2(-32, -32), Vec2(64, 64), color);
    auto rpt = RepeatForever::create(RotateBy::create(0.01, 3));
    auto seq = Sequence::create(DelayTime::create(0.5), FadeOut::create(0.5), CallFunc::create([&, draw](){
        draw->removeFromParentAndCleanup(true);
    }), nullptr);
    draw->runAction(rpt);
    draw->runAction(seq);
    return draw;
//    draw->scheduleOnce([&](float dt) {
//    }, 1, "won");
}


void SplashScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

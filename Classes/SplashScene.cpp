//
//  SplashScene.cpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/17/21.
//

#include "SplashScene.h"
#include "GameScene.h"

USING_NS_CC;

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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto icon = Sprite::createWithSpriteFrameName("title");
    icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    icon->setScale(2);
    icon->setPosition(Vec2::ZERO - icon->getContentSize() * 0.5);
    
    
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

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'exit.png' and 'exit_pressed.png'");
    }
    else
    {
        float x = origin.x + size.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}


void SplashScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

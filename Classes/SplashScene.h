//
//  SplashScene.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/17/21.
//

#ifndef SplashScene_hpp
#define SplashScene_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "UnityAdsNativeAPI.h"
#include "GameScene.h"
#include "PowerUp.h"

class SplashScene : public cocos2d::Scene
{
private:
    cocos2d::Label* titleLabel;
    void doProgress(float dt);
    cocos2d::Node* createSpinnyNode(cocos2d::Vec2 pos, cocos2d::Color4F color);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
    
    // Unity Ads
    void rewardPlayer(const char *placementId);
    void initUnityAdsFunc();
    void showUnityAdsFunc(Ref* pSender);
};

#endif /* SplashScene_hpp */

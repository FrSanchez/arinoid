//
//  SplashScene.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/17/21.
//

#ifndef SplashScene_hpp
#define SplashScene_hpp

#include "cocos2d.h"
#include "GameScene.h"
#include "PowerUp.h"

class SplashScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif /* SplashScene_hpp */

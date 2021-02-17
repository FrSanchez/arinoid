//
//  GameScene.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/11/21.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
private:
    cocos2d::Rect* brickTiles;

public:
    static cocos2d::Scene* createScene();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    virtual bool init();
    void makeLevel();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};
#endif /* GameScene_hpp */

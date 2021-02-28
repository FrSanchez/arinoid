//
//  Ball.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/17/21.
//

#ifndef Ball_hpp
#define Ball_hpp

#include "cocos2d.h"
#include "Arena.h"

#define BALL_TAG 0x31

class Ball : public cocos2d::Sprite
{
    cocos2d::Vec2 _velocity;
    std::function<void(Ball*)> _callback;
public:
    ~Ball();
    void setOnLostBall(std::function<void(Ball*)> callback) { _callback = callback; }
    void pause();
    void unPause();
    void streakUpdate(float dt);
    cocos2d::Node* createShadow(cocos2d::Vec2 pos, cocos2d::Color4F color, cocos2d::Size size);
    virtual bool init();
    CREATE_FUNC(Ball);
};

#endif /* Ball_hpp */

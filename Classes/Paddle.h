//
//  Paddle.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/14/21.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include "cocos2d.h"
#include "Ball.h"

#define PADDLE_TAG 0xa1

enum paddleImages {
    NORMAL = 0,
    SMALL = 1,
    LARGE = 2,
    FIRE = 3,
};

class Paddle : public cocos2d::Sprite
{
private:
    void addPhysicsBody();
    
    std::string _currentFrame;
    float minX, maxX;
    bool _active;
    cocos2d::Size _size0;
public:
    virtual bool init();
    void die(std::function<void()> _callback);
    void start();
    void setPaddleImage(paddleImages image);
    void setArenaWidth(float width);
    void powerUpGrow();
    void powerUpShrink();
    void powerUpEnd();
    void hitBall(Ball* ball);
    CREATE_FUNC(Paddle);

    constexpr static const char * const tiles[4] = { "paddleRed", "paddleBlue", "paddleRed", "paddleRed" };
    
};

#endif /* Paddle_hpp */

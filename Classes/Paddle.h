//
//  Paddle.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/14/21.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include "cocos2d.h"

enum paddleImages {
    NORMAL = 0,
    SMALL = 1,
    LARGE = 2,
    FIRE = 3,
};

class Paddle : public cocos2d::Sprite
{
private:
    std::string _currentFrame;
public:
    virtual bool init();
    void die(std::function<void()> _callback);
    void start();
    void setPaddleImage(paddleImages image);
    CREATE_FUNC(Paddle);

    constexpr static const char * const tiles[4] = { "paddle", "paddleSmall", "paddleLarge", "paddleFire" };
    
};

#endif /* Paddle_hpp */

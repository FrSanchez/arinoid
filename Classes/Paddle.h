//
//  Paddle.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/14/21.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include "cocos2d.h"

class Paddle : public cocos2d::Sprite
{
public:
    virtual bool init();
    void die(std::function<void()> _callback);
    void start();
    CREATE_FUNC(Paddle);
};

#endif /* Paddle_hpp */

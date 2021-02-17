//
//  Brick.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/16/21.
//

#ifndef Brick_hpp
#define Brick_hpp

#include "cocos2d.h"

class Brick : public cocos2d::Sprite
{
    
public:
    virtual bool init(cocos2d::Vec2 pos, int color);
    static Brick* create(cocos2d::Vec2 pos, int color);
    
    static cocos2d::Rect* tiles;
};


#endif /* Brick_hpp */

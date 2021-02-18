//
//  Brick.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/16/21.
//

#ifndef Brick_hpp
#define Brick_hpp

#define TAG_BRICK 0x20

#include "cocos2d.h"

class Brick : public cocos2d::Sprite
{
public:
    virtual bool init(cocos2d::Vec2 pos, int value);
    static Brick* create(cocos2d::Vec2 pos, int value);
    void updateImage();

    typedef struct _brickData {
        int value;
        int hits;
        std::string frame;
    } BrickData;
    
    constexpr static const char * const tiles[10] = { "yellowBrick", "greenBrick", "redBrick", "darkOrangeBrick",
        "purpleBrick", "orangeBrick", "lightBlueBrick", "darkBlueBrick", "lightGrayBrick", "darkGrayBrick"
    };
};


#endif /* Brick_hpp */

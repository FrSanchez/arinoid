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
#include "ExtraPower.h"

class Brick : public cocos2d::Sprite
{
    cocos2d::Size _size0;
public:
    virtual bool init(cocos2d::Vec2 pos, int value);
    static Brick* create(cocos2d::Vec2 pos, int value);
    void updateImage();
    void remove();
    void hit();

    typedef struct _brickData {
        std::string frame;
        int value;
        int hits;
    } BrickData;
    
//    constexpr static const char * const tiles[10] = { "yellowBrick", "greenBrick", "redBrick", "darkOrangeBrick",
//        "purpleBrick", "orangeBrick", "lightBlueBrick", "darkBlueBrick", "lightGrayBrick", "darkGrayBrick"
//    };
//    static const std::string tiles[];
//    const static std::vector<std::string> tiles;
    const static std::vector<BrickData> metadata;

};


#endif /* Brick_hpp */

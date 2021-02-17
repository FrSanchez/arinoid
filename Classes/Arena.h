//
//  Arena.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/13/21.
//

#ifndef Arena_hpp
#define Arena_hpp

#include "cocos2d.h"

class Arena : public cocos2d::Node
{
    int tileSize;
    int topx;
    int topy;
    int numXTiles;
    int numYTiles;
    
    cocos2d::Rect* borders;
    cocos2d::Rect* tiles;
    
    Arena();
    void makeBackground(int tile);
    void drawTile(cocos2d::Rect, int, int);
    
public:
    virtual bool init();
    CREATE_FUNC(Arena);
    ~Arena();
};

#endif /* Arena_hpp */

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
    int numXTiles;
    int numYTiles;
    
    Arena();
    void makeBackground(int tile);
    cocos2d::Sprite* drawTile(std::string frameName, int, int);
    
public:
    static Arena* create(int tileNum);
    virtual bool init(int tileNum);
    ~Arena();
    
    constexpr static const char * const borderNames[8] = { "leftBorder", "rightBorder",
        "leftSpecialBorder", "rightSpecialBorder",
        "plainBorder", "specialBorder", "upperLeftBorder", "upperRightBorder" };
    
    constexpr static const char * const tiles[6] = {"purpleTile","darkBlueTile", "redTile", "greenTile",  "blueTile", "darkPurple"};
    
    constexpr static const int bordertop[] = {6, 4, 4, 4, 5, 4, 4, 4, 4, 5, 4, 4, 4, 7};
    constexpr static const int borderleft[] = {0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0};
    constexpr static const int borderright[] = {1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1};
};

#endif /* Arena_hpp */

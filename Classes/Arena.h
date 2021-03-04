//
//  Arena.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/13/21.
//

#ifndef Arena_hpp
#define Arena_hpp

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

#define ARENA_TAG 0x2f
#define MAX_NUM_TILES 7
class Arena : public cocos2d::Node
{
private:
    int tileSize;
    int numXTiles;
    int numYTiles;
    cocos2d::Rect _arenaRect;
    Arena();
    void makeBackground(int tile);
    cocos2d::Sprite* drawTile(std::string frameName, int, int);

    constexpr static const float dirX[] = {128, 128, -128, -128,  64,  -64,  64,  -64, 0, 0, 64, -64};
    constexpr static const float dirY[] = { 64,  -64,  64,  -64, 128, 128, -128, -128, 64, -64, 0, 0};
    
public:
    static Arena* create(int tileNum);
    virtual bool init(int tileNum);
    ~Arena();
    void setTile(int tileNum);
    cocos2d::Rect getArenaRect() { return _arenaRect; }
    void animateBackground();
    
    constexpr static const char * const borderNames[8] = { "leftBorder", "rightBorder",
        "leftSpecialBorder", "rightSpecialBorder",
        "plainBorder", "specialBorder", "upperLeftBorder", "upperRightBorder" };
    
    constexpr static const char * const tiles[MAX_NUM_TILES] = { "greenSquaresTile", "purpleTile", "darkBlueTile", "redTile", "greenTile",  "blueTile", "darkPurple"};
    
    constexpr static const int bordertop[] = {6, 4, 4, 4, 5, 4, 4, 4, 4, 5, 4, 4, 4, 7};
    constexpr static const int borderleft[] = {0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0};
    constexpr static const int borderright[] = {1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1};
};

#endif /* Arena_hpp */

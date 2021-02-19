//
//  PowerUp.hpp
//  arinoid
//
//  Created by Francisco Sanchez on 2/18/21.
//

#ifndef PowerUp_hpp
#define PowerUp_hpp

#include "cocos2d.h"

#define POWERUP_TAG 0x22

class PowerUp : public cocos2d::Sprite
{
private:
    char _type;
public:
    virtual bool init();
    static PowerUp* create(char);
    PowerUp(char type);
};

#endif /* PowerUp_hpp */

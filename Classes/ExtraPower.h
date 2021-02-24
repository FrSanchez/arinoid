//
//  ExtraPower.hpp
//  Arinoid
//
//  Created by Francisco Sanchez on 2/24/21.
//

#ifndef ExtraPower_hpp
#define ExtraPower_hpp

#include "cocos2d.h"

#define POWERUP_TAG 0x22

typedef std::map<char, std::function<void(void)>> CallbacksMap;

class ExtraPower : public cocos2d::Sprite
{
private:
    char _type;
    std::function<void(void)> _callback;
public:
    virtual bool init();
    static ExtraPower* createWithType(char type);
    ExtraPower(char type);
    void die();
    void caught();
    
    static CallbacksMap callbacksMap;
};


#endif /* ExtraPower_hpp */

//
//  Tower1.h
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#ifndef __tower__Tower1__
#define __tower__Tower1__

#include <stdio.h>
#include "Tower.h"
#include <cocos2d.h>

using namespace cocos2d;

class Tower1:public Tower
{
private:
public:
    virtual bool init();
    
    virtual bool load();
    virtual void update();
    virtual void shoot();
    
    CREATE_FUNC(Tower1);
};

#endif /* defined(__tower__Tower1__) */

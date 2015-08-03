//
//  Tower2.h
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#ifndef __tower__Tower2__
#define __tower__Tower2__

#include <stdio.h>
#include "Tower.h"
#include <cocos2d.h>

using namespace cocos2d;

class Tower2:public Tower
{
private:
public:
    virtual bool init();
    
    virtual bool load();
    virtual void update();
    virtual void shoot();
    
    CREATE_FUNC(Tower2);
};
#endif /* defined(__tower__Tower2__) */

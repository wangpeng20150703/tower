//
//  Bullet.h
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#ifndef __tower__Bullet__
#define __tower__Bullet__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Bullet : public cocos2d::Node
{
private:
    Sprite* m_bulletSprite;

public:
    void update(float delta);
    bool load(std::string fileName);
};

#endif /* defined(__tower__Bullet__) */

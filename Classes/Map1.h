//
//  Map1.h
//  tower
//
//  Created by wangpeng on 15/7/29.
//
//

#ifndef __tower__Map1__
#define __tower__Map1__

#include <stdio.h>
#include "cocos2d.h"

class Map1 : public cocos2d::Layer
{
private:
    cocos2d::Vec2 m_vMapPos;
public:
    void loadMapFile(std::string fileName);
    cocos2d::Vec2 getMapPos();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Map1);
};

#endif /* defined(__tower__Map1__) */

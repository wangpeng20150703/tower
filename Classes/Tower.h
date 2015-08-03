//
//  Tower.h
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#ifndef __tower__Tower__
#define __tower__Tower__

#include <stdio.h>
#include "cocos2d.h"
#include "Map1.h"

using namespace cocos2d;

enum TowerType
{
    RED,YELLOW
};

class Tower : public cocos2d::Node
{
protected:
    Sprite* m_tower;
    TowerType m_eTowerType;
    
public:
    void setPos(Vec2 v);
    Sprite* getTowerSprite();
    Vec2 getPos();
    TowerType getTowerType();
    
    virtual bool init();
    virtual bool load();
    virtual void update();
    virtual void shoot();
    
    void setType(TowerType tp);
    TowerType getType();
    
    CREATE_FUNC(Tower);
};

#endif /* defined(__tower__Tower__) */

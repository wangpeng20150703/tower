//
//  Tower2.cpp
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#include "Tower2.h"

bool Tower2::init()
{
    //////////////////////////////
    // 1. super init first
    m_eTowerType=YELLOW;
    load();
    return true;
}


bool Tower2::load()
{
    m_tower=Sprite::create("tower2.png");
    addChild(m_tower);
    return true;
}


void Tower2::update()
{
    
}


void Tower2::shoot()
{
    
}

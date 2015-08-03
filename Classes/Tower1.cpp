//
//  Tower1.cpp
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#include "Tower1.h"

bool Tower1::init()
{
    //////////////////////////////
    // 1. super init first
    m_eTowerType=RED;
    load();
    return true;
}

bool Tower1::load()
{
    m_tower = Sprite::create("tower1.png");
    addChild(m_tower);
    return true;
}

void Tower1::update()
{
}

void Tower1::shoot()
{
}

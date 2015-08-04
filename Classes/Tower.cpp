//
//  Tower.cpp
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#include "Tower.h"

USING_NS_CC;
// on "init" you need to initialize your instance
bool Tower::init()
{
    //////////////////////////////
    // 1. super init first

    return true;
}

void Tower::setPos(Vec2 v)
{
    m_tower->setPosition(v);
}

Sprite* Tower::getTowerSprite()
{
    return m_tower;
}

Vec2 Tower::getPos()
{
    return m_tower->getPosition();
}

bool Tower::load(std::string fileName)
{
    m_tower = Sprite::create(fileName);
    if (!m_tower) {
        log("load tower::Load ERROR!");
        return false;
    }
    addChild(m_tower);
    return true;
}

void Tower::update()
{
}

void Tower::shoot()
{
}

void Tower::setTowerType(TowerType tp)
{
    m_eTowerType = tp;
}

TowerType Tower::getTowerType()
{
    return m_eTowerType;
}
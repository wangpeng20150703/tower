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
    //    scheduleUpdate();
    return true;
}

void Tower::setPos(Vec2 v)
{
    m_tower->setPosition(v);
    //设置更新
    schedule(schedule_selector(Tower::shoot), 1.0f, kRepeatForever, 0);
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

void Tower::shoot(float delta)
{
    //角色进入范围并且塔不为菜单中的子类
    for (int i=0; i<RoleManager::getInstance()->getRoleVector().size(); i++) {
        if(m_tower->getPosition().getDistance(RoleManager::getInstance()->getRoleVector()[i]->getRoleSpritePos())<=200&&m_bIsMenuTower==false)
        {
            BulletManager::getInstance()->addBulletToGame((bulletType)getTowerType(),this->getParent(), 6, getPos(),RoleManager::getInstance()->getRoleVector()[i]);
            return;
        }
    }
}


void Tower::setTowerType(TowerType tp)
{
    m_eTowerType = tp;
}

TowerType Tower::getTowerType()
{
    return m_eTowerType;
}


void Tower::setIsMenuTower(bool is)
{
    m_bIsMenuTower=is;
}


bool Tower::getIsMenuTower()
{
    return m_bIsMenuTower;
}
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
#include "RoleManager.h"
#include "BulletManager.h"

using namespace cocos2d;

enum TowerType { RED, YELLOW };

class Tower : public cocos2d::Node
{
protected:
    Sprite* m_tower;
    TowerType m_eTowerType;
    bool m_bIsMenuTower;
public:
    //设置、获得是否为菜单中的子类
    void setIsMenuTower(bool is);
    bool getIsMenuTower();
    void setPos(Vec2 v);
    Sprite* getTowerSprite();
    Vec2 getPos();
    virtual bool init();
    virtual bool load(std::string fileName);
    void shoot(float delta);

    void setTowerType(TowerType tp);
    TowerType getTowerType();

    CREATE_FUNC(Tower);
};

#endif /* defined(__tower__Tower__) */

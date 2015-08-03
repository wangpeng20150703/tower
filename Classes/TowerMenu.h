//
//  TowerMenu.h
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#ifndef __tower__TowerMenu__
#define __tower__TowerMenu__

#include <stdio.h>
#include <cocos2d.h>
#include "Tower1.h"
#include "Tower2.h"

using namespace cocos2d;

class TowerMenu : public Node
{
private:
    Vec2 m_vTileCenter;
    std::vector<Tower*> m_vMapTower;
    std::vector<Tower*> m_vTower;
    cocos2d::experimental::TMXTiledMap* m_pMap;
    Vec2 m_vMapOffset;
    bool m_bIsExist;
    TowerMenu* m_towerMenu;
    TowerType m_TowerType;

public:
    void addTower(Ref* obj);
    void listen(Vec2 v, std::vector<Tower*> vTowerVectoer);
    void setPos(Vec2 v, cocos2d::experimental::TMXTiledMap* pMap, Vec2 mapOffset, std::vector<Tower*> vTowerVectoer);
    void release();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    CREATE_FUNC(TowerMenu);
};

#endif /* defined(__tower__TowerMenu__) */

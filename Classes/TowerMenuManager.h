//
//  TowerMenuManager.h
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#ifndef __tower__TowerMenuManager__
#define __tower__TowerMenuManager__

#include <stdio.h>
#include "TowerMenu.h"

using namespace std;

class TowerMenuManager
{
private:
    static TowerMenuManager* m_pInstance;
    TowerMenu* m_towerMenu;
    
public:
    TowerMenu* getTowerMenu();
    void release();
    static TowerMenuManager* getInstance();
    bool addNewTowerMenuToGame(cocos2d::Node* node, int zOrder, Vec2 v, cocos2d::experimental::TMXTiledMap* pMap, Vec2 mapOffset);
};
#endif /* defined(__tower__TowerMenuManager__) */

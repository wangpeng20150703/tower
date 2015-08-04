//
//  TowerManager.h
//  tower
//
//  Created by wangpeng on 15/8/3.
//
//

#ifndef __tower__TowerManager__
#define __tower__TowerManager__

#include <stdio.h>
#include "Tower.h"

using namespace std;

class TowerManager
{
private:
    vector<Tower*> m_vTower;
    static TowerManager* m_pInstance;
    TowerManager();
public:
    static TowerManager* getInstance();
    void addNewTowerToGame(TowerType tp,Node* node,int zOrder,Vec2 vPos);
};
#endif /* defined(__tower__TowerManager__) */

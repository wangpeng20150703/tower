//
//  TowerManager.cpp
//  tower
//
//  Created by wangpeng on 15/8/3.
//
//

#include "TowerManager.h"
#include "Tower.h"

TowerManager::TowerManager(){}

TowerManager * TowerManager::m_pInstance=NULL;//初始化静态数据成员

bool TowerManager::addNewTowerToGame(TowerType tp,Node* node,int zOrder,Vec2 vPos)
{
    Tower* temp=Tower::create();
    switch (tp) {
        case RED:
            temp->load("tower1.png");
            break;
        case YELLOW:
            temp->load("tower2.png");
            break;
    }
    temp->setTowerType(tp);
    temp->setPos(vPos);
    node->addChild(temp,zOrder);
    m_vTower.push_back(temp);
    return true;
}


TowerManager* TowerManager::getInstance()
{
    if(m_pInstance==NULL)
    {
        m_pInstance=new TowerManager();
    }
    return m_pInstance;
}


vector<Tower*>& TowerManager::getTowerVector()
{
    return  m_vTower;
}

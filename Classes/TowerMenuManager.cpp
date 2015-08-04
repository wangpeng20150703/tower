//
//  TowerMenuManager.cpp
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#include "TowerMenuManager.h"

TowerMenuManager* TowerMenuManager::m_pInstance=NULL;
TowerMenuManager* TowerMenuManager::getInstance()
{
    if(m_pInstance==NULL)
    {
        m_pInstance=new TowerMenuManager();
    }
    return m_pInstance;
}


bool TowerMenuManager::addNewTowerMenuToGame(cocos2d::Node* node, int zOrder,Vec2 v, cocos2d::experimental::TMXTiledMap* pMap, Vec2 mapOffset)
{
    m_towerMenu = TowerMenu::create();
    m_towerMenu->setPos(v, pMap, mapOffset);
    node->addChild(m_towerMenu,zOrder);
    return true;
}


TowerMenu* TowerMenuManager::getTowerMenu()
{
    return m_towerMenu;
}


void TowerMenuManager::release()
{
    m_towerMenu->release();
    m_towerMenu=NULL;
}
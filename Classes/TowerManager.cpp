//
//  TowerManager.cpp
//  tower
//
//  Created by wangpeng on 15/8/3.
//
//

#include "TowerManager.h"
#include "Tower.h"
#include "Game.h"

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
    temp->setIsMenuTower(false);
    node->addChild(temp,zOrder);
    m_vTower.push_back(temp);
    Game::setScore(Game::getScore()-10);
    listen(temp);
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


void TowerManager::release()
{
    for (int i=0; i<m_vTower.size(); i++) {
        m_vTower[i]->removeFromParentAndCleanup(true);
    }
    m_vTower.clear();
    NotificationCenter::getInstance()->removeAllObservers(this);
}

void TowerManager::listen(Tower*& tower)
{
    //设置监听
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<Tower*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->getTowerSprite()->convertToNodeSpace(touch->getLocation());
        Rect r = target->getTowerSprite()->getTextureRect();
        
        if (r.containsPoint(locationInNode)) {
            NotificationCenter::getInstance()->postNotification("towerAction", target);
            return true;
        }
        return false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, tower);
}

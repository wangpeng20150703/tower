//
//  TowerAction.cpp
//  tower
//
//  Created by wangpeng on 15/8/24.
//
//

#include "TowerAction.h"
#include "Game.h"
#include "UICallBack.h"
#include "TowerManager.h"

// on "init" you need to initialize your instance
bool TowerAction::init()
{
    if (!MyLayer::init()) {
        return false;
    }
    
    this->loadCsb("towerAction/Layer.csb");
    return true;
}

void TowerAction::notificationHandler(Ref* pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    auto name = node->getName();
    UICallback callback = UICallBack::getTouchUICallback(pSender);
    if (callback.enable) {
        if (callback.name.compare("onTouchUp") == 0) {
            this->removeFromParentAndCleanup(true);
            
            for (std::vector<Tower*>::iterator it=TowerManager::getInstance()->getTowerVector().begin(); it!=TowerManager::getInstance()->getTowerVector().end(); it++) {
                if ((*it)==m_tower) {
                    (*it)->setTowerRange((*it)->getTowerRange()*2);
                }
            }
            
            
        } else if (callback.name.compare("onTouchDelete") == 0) {
            this->removeFromParentAndCleanup(true);
            
            for (std::vector<Tower*>::iterator it=TowerManager::getInstance()->getTowerVector().begin(); it!=TowerManager::getInstance()->getTowerVector().end(); it++) {
                if ((*it)==m_tower) {
                    (*it)->removeFromParentAndCleanup(true);
                    it=TowerManager::getInstance()->getTowerVector().erase(it);
                    return;
                }
            }
            
        }
        return;
    }
}

void TowerAction::setTower(Tower* tower)
{
    m_tower=tower;
}
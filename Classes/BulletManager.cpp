//
//  BulletManager.cpp
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#include "BulletManager.h"

BulletManager* BulletManager::m_pInstance = NULL;

BulletManager* BulletManager::getInstance()
{
    if (m_pInstance == NULL) {
        m_pInstance = new BulletManager();
    }
    return m_pInstance;
}

bool BulletManager::addBulletToGame(std::string fileName, Node* node, int zOrder, Vec2 pos,Role* role)
{
    auto temp = Bullet::create();
    temp->load(fileName);
    node->addChild(temp, zOrder);
    temp->setPos(pos);
    temp->setRole(role);
    m_vBulletVector.push_back(temp);
    return true;
}

std::vector<Bullet*> BulletManager::getBulletVector()
{
    return m_vBulletVector;
}


void BulletManager::update()
{
    if (m_vBulletVector.size()==0) {
        return;
    }
    for (std::vector<Bullet*>::iterator it=m_vBulletVector.begin(); it!=m_vBulletVector.end(); ) {
        if((*it)->getRole()->getCollideRect().containsPoint((*it)->getPos()))
        {
            auto x=(*it)->getRole()->getCollideRect();
            auto y=(*it)->getPos();
            (*it)->removeFromParentAndCleanup(true);
            it=m_vBulletVector.erase(it);
            continue;
        }
        it++;
    }
}




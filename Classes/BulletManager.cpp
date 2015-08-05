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

bool BulletManager::addBulletToGame(std::string fileName, Node* node, int zOrder, Vec2 pos)
{
    auto temp = Bullet::create();
    temp->load(fileName);
    node->addChild(temp, zOrder);
    temp->setPosition(pos);
    return true;
}

std::vector<BulletManager*> BulletManager::getBulletVector()
{
    return m_vBulletVector;
}

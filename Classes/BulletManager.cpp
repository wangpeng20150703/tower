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

bool BulletManager::addBulletToGame(std::string fileName, Node* node, int zOrder, Vec2 pos, Role*& role)
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
    if (m_vBulletVector.size() == 0) {
        return;
    }
    //遍历子弹数组，
    for (std::vector<Bullet*>::iterator it = m_vBulletVector.begin(); it != m_vBulletVector.end();) {
         //如果子弹锁定的目标角色已经
        if ((*it)->getRole() != NULL) {
            //如果与角色碰撞则角色减少当前血量，子弹删除
            if ((*it)->getRole()->getCollideRect().containsPoint((*it)->getPos())) {
                (*it)->getRole()->setRoleCurrntLife((*it)->getRole()->getRoleCurrntLife() - 15);

                //如果当前子弹碰撞的角色的血量为0
                if ((*it)->getRole()->getRoleCurrntLife() <= 0) {
                    //遍历角色数组
                    for (std::vector<Role*>::iterator itR = RoleManager::getInstance()->getRoleVector().begin();
                         itR != RoleManager::getInstance()->getRoleVector().end();) {
                        //如果当前生命值为0的角色就是当前遍历到的角色、删除当前生命值为0的角色数组中的角色
                        if (*itR == (*it)->getRole()) {
                            (*itR)->removeFromParentAndCleanup(true);
                            itR = RoleManager::getInstance()->getRoleVector().erase(itR);
                            //遍历子弹数组
                            for (std::vector<Bullet*>::iterator itB = m_vBulletVector.begin();
                                 itB != m_vBulletVector.end();) {
                                //如果子弹列表中还
                                if ((*itB)->getRole() == (*it)->getRole() && (*it) != (*itB)) {
                                    //                                (*itB)->removeFromParentAndCleanup(true);
                                    //                                itB = m_vBulletVector.erase(itB);
                                    Role* r = NULL;
                                    (*itB)->setRole(r);
                                    continue;
                                }
                                itB++;
                            }
                            continue;
                        }
                        itR++;
                    }
                }
                (*it)->removeFromParentAndCleanup(true);
                it = m_vBulletVector.erase(it);
                continue;
            }
        }
        it++;
    }
}

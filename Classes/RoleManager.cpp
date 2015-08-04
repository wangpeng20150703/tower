//
//  RoleManager.cpp
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#include "RoleManager.h"

RoleManager* RoleManager::m_pInstance=NULL;
RoleManager* RoleManager::getInstance()
{
    if(m_pInstance==NULL)
    {
        m_pInstance=new RoleManager();
    }
    return m_pInstance;
}


bool RoleManager::addNewRoleToGame(roleType tp,cocos2d::Node* node,int zOrder,cocos2d::experimental::TMXTiledMap * map,char dir,cocos2d::Vec2 mapPos,cocos2d::Vec2 roleStartPos)
{
    auto role = Role::create();
    node->addChild(role,zOrder);
    switch (tp) {
        case ROLE1:
            role->load("role.png");
            break;
            
        case ROLE2:
            role->load("role2.png");
            break;
    }
    role->setMap(map);
    role->setCurrntDirection('d');
    role->getMapPos(mapPos);
    role->setStartPosition(roleStartPos);  //这里的位置应该为在地图上的相对位置，即忽略地图相对屏幕的移动
    m_vRoleVector.push_back(role);
    return true;
}


vector<Role*> RoleManager::getRoleVector()
{
    return m_vRoleVector;
}
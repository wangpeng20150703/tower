//
//  RoleManager.h
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#ifndef __tower__RoleManager__
#define __tower__RoleManager__

#include <stdio.h>
#include "Role.h"

using namespace std;

class RoleManager:public cocos2d::Node
{
private:
    static RoleManager* m_pInstance;
    vector<Role*> m_vRoleVector;
    int m_iDeadRole;
    int m_iSuccessRole;
    Vec2 m_vRoleEndPos;
    
public:
    void successRoleOne();
    int getSuccessRole();
    void deadRoleAddOne();
    int getDeadRole();
    void setDeadRole(int iDeadRole);
    void release();
    void update();
    vector<Role*>& getRoleVector();
    static RoleManager* getInstance();
    bool addNewRoleToGame(roleType tp, cocos2d::Node* node, int zOrder, cocos2d::experimental::TMXTiledMap* map, char dir, cocos2d::Vec2 pos,cocos2d::Vec2 roleStartPos,Vec2 roleEndPos);
};

#endif /* defined(__tower__RoleManager__) */

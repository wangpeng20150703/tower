//
//  RoleManager.cpp
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#include "RoleManager.h"

RoleManager* RoleManager::m_pInstance = NULL;
RoleManager* RoleManager::getInstance()
{
    if (m_pInstance == NULL) {
        m_pInstance = new RoleManager();
    }
    return m_pInstance;
}

bool RoleManager::addNewRoleToGame(roleType tp,
                                   cocos2d::Node* node,
                                   int zOrder,
                                   cocos2d::experimental::TMXTiledMap* map,
                                   char dir,
                                   cocos2d::Vec2 mapPos,
                                   cocos2d::Vec2 roleStartPos,
                                   Vec2 roleEndPos)
{
    auto role = Role::create();

    //读取角色配置文件
    std::string path = FileUtils::getInstance()->fullPathForFilename("roleData.ini");
    FILE* pf = fopen(path.c_str(), "r");
    if (!pf) {
        log("OpenRoleFileError");
    }
    int type;
    char fileName[16];
    int life;
    do {
        fscanf(pf, "%d", &type);
        fscanf(pf, "%d", &life);
    } while (type != tp);

    sprintf(fileName, "role%d.png", type);
    role->load(fileName);

    //添加角色传递信息
    role->setMap(map);
    role->setCurrntDirection(dir);
    role->getMapPos(mapPos);
    role->setStartPosition(roleStartPos);  //这里的位置应该为在地图上的相对位置，即忽略地图相对屏幕的移动
    m_vRoleEndPos = roleEndPos;

    role->setRoleTotalLife(life);
    role->setRoleCurrntLife(life);

    //添加角色到父层
    node->addChild(role, zOrder);
    m_vRoleVector.push_back(role);

    return true;
}

vector<Role*>& RoleManager::getRoleVector()
{
    return m_vRoleVector;
}

void RoleManager::update()
{
    if (m_vRoleVector.size() == 0) {
        return;
    }
    for (std::vector<Role*>::iterator it = m_vRoleVector.begin(); it != m_vRoleVector.end();) {
        auto x = (*it)->getRolePosInMapTile();
        if ((int)((*it)->getRolePosInMapTile().x) == m_vRoleEndPos.x &&
            (int)((*it)->getRolePosInMapTile().y) == m_vRoleEndPos.y) {
            (*it)->removeFromParentAndCleanup(true);
            it = m_vRoleVector.erase(it);
            m_iSuccessRole++;
            continue;
        }
        it++;
    }
}

void RoleManager::release()
{
    for (int i = 0; i < m_vRoleVector.size(); i++) {
        m_vRoleVector[i]->removeFromParentAndCleanup(true);
    }
    m_iDeadRole = 0;
    m_iSuccessRole=0;
    m_vRoleVector.clear();
}

int RoleManager::getDeadRole()
{
    return m_iDeadRole;
}

void RoleManager::setDeadRole(int iDeadRole)
{
    m_iDeadRole = iDeadRole;
}

void RoleManager::deadRoleAddOne()
{
    m_iDeadRole++;
}


void RoleManager::successRoleOne()
{
    m_iSuccessRole++;
}
int RoleManager::getSuccessRole()
{
    return m_iSuccessRole;
}
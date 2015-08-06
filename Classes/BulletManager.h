//
//  BulletManager.h
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#ifndef __tower__BulletManager__
#define __tower__BulletManager__

#include <stdio.h>
#include "cocos2d.h"
#include "Bullet.h"
#include "RoleManager.h"

using namespace cocos2d;

class BulletManager
{
private:
    static BulletManager* m_pInstance;
    std::vector<Bullet*> m_vBulletVector;
public:
    void update();
    std::vector<Bullet*> getBulletVector();
    static BulletManager* getInstance();
    bool addBulletToGame(std::string fileName,Node* node,int zOrder,Vec2 pos,Role*& role);
};

#endif /* defined(__tower__BulletManager__) */

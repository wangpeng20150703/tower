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

using namespace cocos2d;

class BulletManager
{
private:
    static BulletManager* m_pInstance;
    std::vector<BulletManager*> m_vBulletVector;
public:
    std::vector<BulletManager*> getBulletVector();
    static BulletManager* getInstance();
    bool addBulletToGame(std::string fileName,Node* node,int zOrder,Vec2 pos);
};

#endif /* defined(__tower__BulletManager__) */

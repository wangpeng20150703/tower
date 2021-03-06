//
//  Bullet.h
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#ifndef __tower__Bullet__
#define __tower__Bullet__

#include <stdio.h>
#include "cocos2d.h"
#include "Role.h"

enum bulletType
{
    BULLET0,BULLET1
};

using namespace cocos2d;

class Bullet : public cocos2d::Node
{
private:
    Sprite* m_bulletSprite;
    Role* m_roleAim;
    Vec2 m_vDirection;
    int m_iAtk;
    
public:
    void setAtk(int atk);
    int getAtk();
    void setPos(Vec2 v);
    Vec2 getPos();
    void setRole(Role*& role);
    Role*& getRole();
    virtual bool init();
    void update(float delta);
    bool load(std::string fileName);
    CREATE_FUNC(Bullet);
};

#endif /* defined(__tower__Bullet__) */

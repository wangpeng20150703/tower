//
//  Bullet.cpp
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#include "Bullet.h"

bool Bullet::init()
{
    return true;
}

bool Bullet::load(std::string fileName)
{
    m_bulletSprite = Sprite::create(fileName);
    if (NULL == m_bulletSprite) {
        log("bulletSpriteCreatError");
        return false;
    }
    addChild(m_bulletSprite);
    return true;
}

void Bullet::update(float delta)
{
    //获得
    Vec2 single;
    single.set(m_bulletSprite->getPosition(), m_roleAim->getCollidePoint());
    single.normalize();
    single*=6;
    m_bulletSprite->setPosition(m_bulletSprite->getPosition()+single);
}

void Bullet::setRole(Role* role)
{
    m_roleAim = role;
    scheduleUpdate();
}

void Bullet::setPos(Vec2 v)
{
    m_bulletSprite->setPosition(v);
}


Vec2 Bullet::getPos()
{
    return m_bulletSprite->getPosition();
}


Role* Bullet::getRole()
{
    return  m_roleAim;
}

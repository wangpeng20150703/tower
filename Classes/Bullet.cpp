//
//  Bullet.cpp
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#include "Bullet.h"
#include "BulletManager.h"

bool Bullet::init()
{
    return true;
}

bool Bullet::load(std::string fileName)
{
    m_bulletSprite = Sprite::create(fileName);
    if (NULL == m_bulletSprite) {
        log("bulletSpriteCreatError,BulletLoadError");
        return false;
    }
    addChild(m_bulletSprite);
    return true;
}

void Bullet::update(float delta)
{
    if (m_bulletSprite==NULL) {
        log("bulletLoadError,BulletUpdateReturnNull");
        return;
    }
    if(m_roleAim!=NULL)
    {
        m_vDirection.set(m_bulletSprite->getPosition(), m_roleAim->getCollidePoint());
    }
    m_vDirection.normalize();
    
    m_vDirection*=3;
    m_bulletSprite->setPosition(m_bulletSprite->getPosition()+m_vDirection);
}

void Bullet::setRole(Role*& role)
{
    m_roleAim = role;
    if (m_roleAim==NULL) {
        log("bulletSetRoleIsNull");
        return;
    }
    scheduleUpdate();
}

void Bullet::setPos(Vec2 v)
{
    if (m_bulletSprite==NULL) {
        log("bulletSpriteIsNull,SetPosIsError");
        return;
    }
    m_bulletSprite->setPosition(v);
}


Vec2 Bullet::getPos()
{
    if (m_bulletSprite==NULL) {
        log("bulletSpriteIsNull,GetPosIsNull");
        return NULL;
    }
    return m_bulletSprite->getPosition();
}


Role*& Bullet::getRole()
{
    if (m_roleAim==NULL) {
        log("roleAimIsNull,GetRoleIsNull");
    }
    return  m_roleAim;
}


void Bullet::setAtk(int atk)
{
    m_iAtk=atk;
}
int Bullet::getAtk()
{
    return m_iAtk;
}

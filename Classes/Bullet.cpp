//
//  Bullet.cpp
//  tower
//
//  Created by wangpeng on 15/8/4.
//
//

#include "Bullet.h"

bool Bullet::load(std::string fileName)
{
    m_bulletSprite = Sprite::create(fileName);
    if (NULL == m_bulletSprite) {
        log("bulletSpriteCreatError");
        return false;
    }
    return true;
}

void Bullet::update(float delta)
{
    
}

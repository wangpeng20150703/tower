//
//  Role.cpp
//  tower
//
//  Created by wangpeng on 15/7/29.
//
//

#include "Role.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Role::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }
    setAction();
    return true;
}

void Role::setAction()
{
    auto s = Director::getInstance()->getWinSize();

    auto texture = Director::getInstance()->getTextureCache()->addImage("role.png");

    for (int i = 0; i < 4; i++) {
        auto frame0 = SpriteFrame::createWithTexture(texture, Rect(32 * 0, 48 * i, 32, 48));
        auto frame1 = SpriteFrame::createWithTexture(texture, Rect(32 * 1, 48 * i, 32, 48));
        auto frame2 = SpriteFrame::createWithTexture(texture, Rect(32 * 2, 48 * i, 32, 48));
        auto frame3 = SpriteFrame::createWithTexture(texture, Rect(32 * 3, 48 * i, 32, 48));

        Vector<SpriteFrame*> animFrames(4);
        animFrames.pushBack(frame0);
        animFrames.pushBack(frame1);
        animFrames.pushBack(frame2);
        animFrames.pushBack(frame3);
        m_sprDirection[i] = Sprite::createWithSpriteFrame(frame0);
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
        auto animate = Animate::create(animation);
        m_seqDirecrion[i] = Sequence::create(animate, nullptr);
        animFrames.empty();
    }
}

// move
void Role::run()
{
    int x = m_sprCurrntDirection->getPositionX() - m_vMapPos.x;
    int y = m_sprCurrntDirection->getPositionY() - m_vMapPos.y;
    int h = m_map->getMapSize().height - 1;

    int width = m_map->getTileSize().width;
    int height = m_map->getTileSize().height;

    //    for(int i=0;i<4;i++)
    //    {
    //        if(m_sprDirection[i]!=m_sprCurrntDirection)
    //        {
    //            m_sprDirection[i]->setPosition(m_sprCurrntDirection->getPosition());
    //        }
    //    }

    switch (m_dirCurrntDirection) {
        case UP:
            if (m_mapLayer->getTileGIDAt(Vec2(x / width, h - (y + 1 + height / 2) / height)) == 1) {
                m_sprCurrntDirection->setPositionY(m_sprCurrntDirection->getPositionY() + 1);
            } else {
                setCurrntDirection('d');
            }
            break;
        case DOWN:
            if (m_mapLayer->getTileGIDAt(Vec2(x / width, h - (y - 1 - height / 2) / height)) == 1) {
                m_sprCurrntDirection->setPositionY(m_sprCurrntDirection->getPositionY() - 1);
            } else {
                setCurrntDirection('a');
            }
            break;
        case LEFT:
            if (m_mapLayer->getTileGIDAt(Vec2((x - 1 - width / 2) / width, h - y / height)) == 1) {
                m_sprCurrntDirection->setPositionX(m_sprCurrntDirection->getPositionX() - 1);
            } else {
                setCurrntDirection('w');
            }
            break;
        case RIGHT:
            int x1 = m_sprCurrntDirection->getPositionX();
            int x2 = (x + 1 + width / 2) / width;
            int x3 = h - y / height;
            int x4 = m_mapLayer->getTileGIDAt(Vec2((x + 1 + width / 2) / width, h - y / height));
            if (m_mapLayer->getTileGIDAt(Vec2((x + 1 + width / 2) / width, h - y / height)) == 1) {
                m_sprCurrntDirection->setPositionX(m_sprCurrntDirection->getPositionX() + 1);
            } else {
                setCurrntDirection('s');
            }
            break;
    }
}

void Role::setStartPosition(cocos2d::Vec2 vPos)
{
    vPos = vPos + m_vMapPos;
    m_sprCurrntDirection->setPosition(vPos);
    addChild(m_sprCurrntDirection, 100);
    m_sprCurrntDirection->setScale(3.0f);
    m_sprCurrntDirection->setAnchorPoint(Point(0.5, 0.08));
}

cocos2d::Vec2 Role::getPosition()
{
    return m_sprCurrntDirection->getPosition();
}

void Role::setCurrntDirection(char dir)
{
    switch (dir) {
        case 'w':
            m_sprCurrntDirection = m_sprDirection[0];
            m_sprCurrntDirection->runAction(RepeatForever::create(m_seqDirecrion[3]));
            m_dirCurrntDirection = UP;
            break;
        case 'a':
            m_sprCurrntDirection = m_sprDirection[1];
            m_sprCurrntDirection->runAction(RepeatForever::create(m_seqDirecrion[1]));
            m_dirCurrntDirection = LEFT;
            break;
        case 's':
            m_sprCurrntDirection = m_sprDirection[3];
            m_sprCurrntDirection->runAction(RepeatForever::create(m_seqDirecrion[0]));
            m_dirCurrntDirection = DOWN;
            break;
        case 'd':
            m_sprCurrntDirection = m_sprDirection[2];
            m_sprCurrntDirection->runAction(RepeatForever::create(m_seqDirecrion[2]));
            m_dirCurrntDirection = RIGHT;
            break;
    }
}

void Role::getMapPos(cocos2d::Vec2 pos)
{
    m_vMapPos = pos;
}

void Role::getMapFileName(std::string mapFileName)
{
    m_map = cocos2d::experimental::TMXTiledMap::create(mapFileName);
    m_mapLayer = m_map->getLayer("layer0");
}

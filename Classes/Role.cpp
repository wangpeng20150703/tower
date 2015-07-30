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

    m_sprCurrntDirection = NULL;

    return true;
}

void Role::setAction(Vec2 v)
{
    if (m_sprCurrntDirection) {
        return;
    }

    auto s = Director::getInstance()->getWinSize();

    auto texture = Director::getInstance()->getTextureCache()->addImage("role.png");

    auto frame0 = SpriteFrame::createWithTexture(texture, Rect(32 * 0, 48 * m_dirCurrntDirection, 32, 48));
    auto frame1 = SpriteFrame::createWithTexture(texture, Rect(32 * 1, 48 * m_dirCurrntDirection, 32, 48));
    auto frame2 = SpriteFrame::createWithTexture(texture, Rect(32 * 2, 48 * m_dirCurrntDirection, 32, 48));
    auto frame3 = SpriteFrame::createWithTexture(texture, Rect(32 * 3, 48 * m_dirCurrntDirection, 32, 48));

    m_sprCurrntDirection = Sprite::createWithSpriteFrame(frame0);

    Vector<SpriteFrame*> animFrames;
    animFrames.pushBack(frame0);
    animFrames.pushBack(frame1);
    animFrames.pushBack(frame2);
    animFrames.pushBack(frame3);

    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    auto animate = Animate::create(animation);
    Sequence* sequence = Sequence::create(animate, nullptr);

    m_sprCurrntDirection->runAction(RepeatForever::create(sequence));
    m_sprCurrntDirection->setPosition(v);

    m_sprCurrntDirection->setScale(3.0f);
    m_sprCurrntDirection->setAnchorPoint(Point(0.5, 0.08));
    addChild(m_sprCurrntDirection);
}

// move
void Role::run()
{
    if (m_sprCurrntDirection == NULL) {
        return;
    }
    float fX = (getPosition().x - m_vMapPos.x) / m_fTileWidth;
    float fY = m_iMapHeight - (getPosition().y - m_vMapPos.y) / m_fTileHeight;

    int iX = fX;
    int iY = fY;
//    CCLOG("%d,%d", iX, iY);
    switch (m_dirCurrntDirection) {
        case UP: {
            m_sprCurrntDirection->setPositionY(m_sprCurrntDirection->getPositionY() + 1);
            if (getMapDate(Vec2(iX, iY - 1)) != 1) {
                if (fY - iY < 0.8) {
                    if (getMapDate(Vec2(iX + 1, iY)) == 1) {
                        setCurrntDirection('d');
                    } else {
                        setCurrntDirection('a');
                    }
                }
            }
        } break;
        case DOWN: {
            m_sprCurrntDirection->setPositionY(m_sprCurrntDirection->getPositionY() - 1);
            if (getMapDate(Vec2(iX, iY + 1)) != 1) {
                if (fY - iY > 0.8) {
                    if (getMapDate(Vec2(iX + 1, iY)) == 1) {
                        setCurrntDirection('d');
                    } else {
                        setCurrntDirection('a');
                    }
                }
            }

        }

        break;
        case LEFT: {
            m_sprCurrntDirection->setPositionX(m_sprCurrntDirection->getPositionX() - 1);
            if (getMapDate(Vec2(iX - 1, iY)) != 1) {
                if (fX - iX < 0.5) {
                    if (getMapDate(Vec2(iX, iY - 1)) == 1) {
                        setCurrntDirection('w');
                    } else {
                        setCurrntDirection('s');
                    }
                }
            }
        }

        break;
        case RIGHT: {
            m_sprCurrntDirection->setPositionX(m_sprCurrntDirection->getPositionX() + 1);
            if (getMapDate(Vec2(iX + 1, iY)) != 1) {
                if (fX - iX > 0.5) {
                    if (getMapDate(Vec2(iX, iY - 1)) == 1) {
                        setCurrntDirection('w');
                    } else {
                        setCurrntDirection('s');
                    }
                }
            }
        } break;
    }
}

int Role::getMapDate(cocos2d::Vec2 v)
{
    return m_ppMapData[(int)v.x][(int)v.y];
}

void Role::setStartPosition(cocos2d::Vec2 vPos)
{
    vPos = vPos + m_vMapPos;
    m_sprCurrntDirection->setPosition(vPos);
    //    addChild(m_sprCurrntDirection, 100);
}

//返回结果为地图相对位置
cocos2d::Vec2 Role::getPosition()
{
    return m_sprCurrntDirection->getPosition();
}

void Role::setPosition(cocos2d::Vec2 pos)
{
    m_sprCurrntDirection->cocos2d::Node::setPosition(pos);
}

void Role::setCurrntDirection(char dir)
{
    Vec2 v;
    if (m_sprCurrntDirection != NULL) {
        v = m_sprCurrntDirection->getPosition();

        m_sprCurrntDirection->getParent()->removeChild(m_sprCurrntDirection);
        m_sprCurrntDirection = NULL;
    }

    switch (dir) {
        case 'w': m_dirCurrntDirection = UP; break;
        case 'a': m_dirCurrntDirection = LEFT; break;
        case 's': m_dirCurrntDirection = DOWN; break;
        case 'd': m_dirCurrntDirection = RIGHT; break;
    }

    setAction(v);
    if (m_sprCurrntDirection->getPosition() == Vec2(0, 0)) {
        m_sprCurrntDirection->setPosition(v);
    }
}

void Role::getMapPos(cocos2d::Vec2 pos)
{
    m_vMapPos = pos;
}

void Role::setMap(cocos2d::experimental::TMXTiledMap* map)
{
    // auto map = cocos2d::experimental::TMXTiledMap::create(mapFileName);
    m_iMapHeight = map->getMapSize().height;
    auto layer = map->getLayer("layer0");
    m_fTileWidth = map->getTileSize().width;
    m_fTileHeight = map->getTileSize().height;

    m_ppMapData = new int*[(int)map->getMapSize().width];
    for (int i = 0; i < (int)map->getMapSize().width; i++) {
        m_ppMapData[i] = new int[(int)map->getMapSize().height];
    }

    for (int i = 0; i < (int)map->getMapSize().width; i++) {
        for (int j = 0; j < (int)map->getMapSize().height; j++) {
            m_ppMapData[i][j] = layer->getTileGIDAt(Vec2(i, j));
        }
    }
}
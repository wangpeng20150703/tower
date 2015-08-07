//
//  Map1.cpp
//  tower
//
//  Created by wangpeng on 15/7/29.
//
//

#include "Map1.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Map1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}


Vec2 Map1::getMapPos()
{
    return m_vMapPos;
}


void Map1::loadMapFile(std::string fileName)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_map = cocos2d::experimental::TMXTiledMap::create(fileName);
    float mapPositionX=visibleSize.width-(m_map->getTileSize()).width*m_map->getMapSize().width;
    m_map->setPositionX(mapPositionX/2);
    addChild(m_map, 0, 0);
    m_vMapPos=m_map->getPosition();
}


cocos2d::experimental::TMXTiledMap * Map1::getMap()
{
    return m_map;
}
//
//  Role.h
//  tower
//
//  Created by wangpeng on 15/7/29.
//
//

#ifndef __tower__Role__
#define __tower__Role__

#include <stdio.h>
#include "cocos2d.h"
#include "Map1.h"

enum dir
{
    UP,RIGHT,DOWN,LEFT
};


class Role: public cocos2d::Layer
{
private:
    cocos2d::Sprite* m_sprDirection[4];
    cocos2d::Sequence* m_seqDirecrion[4];
    cocos2d::Sprite* m_sprCurrntDirection;
    dir m_dirCurrntDirection;
    cocos2d::Vec2 m_vMapPos;//获得同一场景下的地图的位置
    cocos2d::experimental::TMXTiledMap * m_map;//角色需要获得地图的信息
    cocos2d::experimental::TMXLayer* m_mapLayer;
public:
    void getMapFileName(std::string mapFileName);
    void getMapPos(cocos2d::Vec2 pos);
    void setAction();
    void run();
    void setCurrntDirection(char dir);
    cocos2d::Vec2 getPosition();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void setStartPosition(cocos2d::Vec2 vPos);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Role);
};

#endif /* defined(__tower__Role__) */

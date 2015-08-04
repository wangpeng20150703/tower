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

enum dir { DOWN, LEFT, RIGHT, UP };

enum roleType
{
    ROLE1,ROLE2
};

class Role : public cocos2d::Node
{
private:
    cocos2d::Sprite* m_sprCurrntDirection;
    dir m_dirCurrntDirection;
    cocos2d::Vec2 m_vMapPos;  //获得同一场景下的地图的位置
    int m_iMapHeight;
    float m_fTileWidth;
    float m_fTileHeight;
    int** m_ppMapData;
    cocos2d::Texture2D * m_pTexture;
    
public:
    bool load(std::string fileName);
    void setMap(cocos2d::experimental::TMXTiledMap * map);
    void getMapFileName(std::string mapFileName);
    void getMapPos(cocos2d::Vec2 pos);
    void setAction(cocos2d::Vec2 v);
    void run();
    void setCurrntDirection(char dir);
    cocos2d::Vec2 getPosition();
    void setPosition(cocos2d::Vec2 pos);
    int getMapDate(cocos2d::Vec2 v);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void setStartPosition(cocos2d::Vec2 vPos);

    // implement the "static create()" method manually
    CREATE_FUNC(Role);
};

#endif /* defined(__tower__Role__) */

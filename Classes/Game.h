//
//  Game.h
//  tower
//
//  Created by wangpeng on 15/7/29.
//
//

#ifndef __tower__Game__
#define __tower__Game__

#include <stdio.h>
#include <string>
#include "cocos2d.h"
#include "Map1.h"
#include "RoleManager.h"
#include "TowerMenuManager.h"

using namespace std;
using namespace cocos2d;

class Game : public cocos2d::Layer
{
private:
    static int m_iCurrntGame;
    
    bool m_bIsTowerMenuExist;//塔菜单是否存在
    Map1* m_map;//地图
    float m_fIntertal;//角色产生时间延迟
    int m_iCount;//角色数量
    TowerMenu* m_towerMenu;//塔菜单
    int m_iGame;//读取关卡
    Vec2 m_vRoleStartPos;//角色起始位置
    int m_iRoleType;//角色类型、ini读入、角色创建时使用
    char m_cStartDirection;
    Vec2 m_vRoleEndPos;
    
public:
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void readData();//读取数据

    void readInitFile();
    void readTxt();
    void makeRole(float dt);
    void update(float delta);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};
#endif /* defined(__tower__Game__) */

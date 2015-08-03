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
#include "Role.h"
#include "Tower1.h"
#include "Tower2.h"
#include "TowerMenu.h"

using namespace std;
using namespace cocos2d;

class Game : public cocos2d::Layer
{
private:
    bool m_bIsTowerMenuExist;
    Tower* m_tower;
    Map1* m_map;
    float m_fIntertal;
    int m_iCount;
    std::vector<Role*> m_vRole;
    TowerMenu* m_towerMenu;
    std::vector<Tower*> m_vTowerVector;

public:
    vector<Tower*>& getTowerVector();
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void readData();//保存数据
    void writeData();//读取数据

    void readInitFile();
    void readTxt();
    void makeRole(float dt);
    void update(float delta);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};
#endif /* defined(__tower__Game__) */

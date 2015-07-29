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
#include "cocos2d.h"
#include "Map1.h"
#include "Role.h"
class Game : public cocos2d::Layer
{
private:
    Map1* m_map;
    Role* m_role;

public:
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

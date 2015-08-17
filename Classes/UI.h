//
//  UI.h
//  tower
//
//  Created by wangpeng on 15/8/13.
//
//

#ifndef __tower__UI__
#define __tower__UI__

#include <stdio.h>
#include "cocos2d.h"

#include "UICallBackReader.h"

using namespace cocos2d;

class UI : public Layer
{
private:
    static UI* m_pInstance;
public:
    UI();
    static UI* getInstance();
    void menu();
    void nextGame();
    void end(Ref* obj);
    void gameover();
    void start();
    
    virtual void onEnter();
    virtual void onExit();
    CREATE_FUNC(UI)
};

#endif /* defined(__tower__UI__) */

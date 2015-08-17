//
//  UICallBack.h
//  cocostudio
//
//  Created by wangpeng on 15/8/12.
//
//

#ifndef __cocostudio__UICallBack__
#define __cocostudio__UICallBack__

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

using namespace std;

struct UICallback {
    bool enable = false;
    string name = "";
    string customProperty = "";
};

class UICallBack : public cocos2d::Node, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
    static UICallback getTouchUICallback(cocos2d::Ref* object);

    void releaseRunningScene();

    CREATE_FUNC(UICallBack)
    UICallBack();
    virtual cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string& callBackName);

    void onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type);

private:
};
#endif /* defined(__cocostudio__UICallBack__) */


//    //触摸抬起
//    if(type==cocos2d::ui::Widget::TouchEventType::ENDED)
//    {
//        //结束按钮：Logout
//        if (((Node*)object)->getName()=="Button_logout") {
//            //UI中的gameoverAPI接受消息
//            NotificationCenter::getInstance()->postNotification("end", NULL);
//        }
//        //开始按钮：Login
//        else if(((Node*)object)->getName()=="Button_login")
//        {
//            //创建游戏
//            releaseRunningScene();
//            auto layer = Game::create();
//            layer->readData(Game::getCurrntGame());
//            Director::getInstance()->getRunningScene()->addChild(layer);
//        }
//        //失败后重新开始按钮
//        else if(((Node*)object)->getName()=="Button_restart")
//        {
//            releaseRunningScene();
//            auto layer = Game::create();
//            layer->readData(Game::getCurrntGame());
//            Director::getInstance()->getRunningScene()->addChild(layer);
//        }
//        //过关后进入下一关按钮
//        else if(((Node*)object)->getName()=="Button_nextGame")
//        {
//            if (Director::getInstance()->getRunningScene()) {
//                Director::getInstance()->getRunningScene()->removeAllChildren();
//            }
//            auto layer = Game::create();
//            layer->readData(Game::getCurrntGame());
//            Director::getInstance()->getRunningScene()->addChild(layer);
//        }
//        else if(((Node*)object)->getName()=="Button_toStart")
//        {
//            releaseRunningScene();
//            Scene* scene = Scene::create();
//            scene->addChild(UI::getInstance());
//            UI::getInstance()->start();
//            Director::getInstance()->replaceScene(TransitionShrinkGrow::create(3.0, scene));
//        }
//        else if(((Node*)object)->getName()=="Button_back")
//        {
//            NotificationCenter::getInstance()->postNotification("back");
//        }
//    }
//}

//
//  UICallBack.cpp
//  cocostudio
//
//  Created by wangpeng on 15/8/12.
//
//

#include "UICallBack.h"
#include "ui/UIText.h"

#include "cocostudio/CCObjectExtensionData.h"

#include "SimpleAudioEngine.h"
#include "UI.h"
#include "Game.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
using namespace CocosDenshion;

UICallBack::UICallBack()
{
}

Widget::ccWidgetTouchCallback UICallBack::onLocateTouchCallback(const string& callBackName)
{
    CCLOG("onTouchLogoutEnd");
    if (callBackName == "onTouch")  //判断事件名，返回对应的函数。下同
    {
        return CC_CALLBACK_2(UICallBack::onTouch, this);
    }
    return nullptr;
}

void UICallBack::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    //触摸抬起
    switch (type) {
        case Widget::TouchEventType::BEGAN: break;
        case Widget::TouchEventType::MOVED: break;
        case Widget::TouchEventType::ENDED: {
            UICallback callback = UICallBack::getTouchUICallback(object);
            if (callback.enable) {
                CCLOG("callback name : %s", callback.name.c_str());
                NotificationCenter::getInstance()->postNotification(callback.name);
            }
            break;
        }
        case Widget::TouchEventType::CANCELED: break;
        default: break;
    }
}


void UICallBack::releaseRunningScene()
{
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->getRunningScene()->removeAllChildren();
    }
}

UICallback UICallBack::getTouchUICallback(cocos2d::Ref* object)
{
    UICallback callback;
    cocos2d::ui::Widget* widget = dynamic_cast<cocos2d::ui::Widget*>(object);
    if (widget) {
        std::string callbackType = widget->getCallbackType();  // Touch Click Event
        std::string callbackName = widget->getCallbackName();
        if ((callbackType.compare("Touch") == 0) && (callbackName.compare("") != 0)) {
            callback.enable = true;
            callback.name = callbackName;
            callback.customProperty = ((cocostudio::ObjectExtensionData*)(widget->getUserObject()))->getCustomProperty();
        }
    }
    return callback;
}

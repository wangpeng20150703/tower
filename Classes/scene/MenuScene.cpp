//
//  MenuScene.cpp
//  tower
//
//  Created by wangpeng on 15/8/18.
//
//

#include "MenuScene.h"
#include "UICallBack.h"

#include "Game.h"

#include "Start.h"
#include "Volume.h"

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    if (!MyLayer::init()) {
        return false;
    }

    this->loadCsb("menu/Layer.csb");

    return true;
}

void MenuScene::notificationHandler(Ref* pSender)
{
    UICallback callback = UICallBack::getTouchUICallback(pSender);
    if (callback.enable) {
        if (callback.name.compare("onTouchRestart") == 0) {
            Director::getInstance()->replaceScene(Game::createScene());
        } else if (callback.name.compare("onTouchToStart") == 0) {
            Director::getInstance()->replaceScene(Start::createScene());
        } else if (callback.name.compare("onTouchBack") == 0) {
            this->removeFromParentAndCleanup(true);
            NotificationCenter::getInstance()->postNotification("back");
        } else if (callback.name.compare("onTouchLogout") == 0) {
            //删除所有的child包括UI
            Director::getInstance()->getRunningScene()->removeAllChildren();
            Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        } else if (callback.name.compare("onTouchVolume") == 0) {
            auto layer = Volume::create();
            Director::getInstance()->getRunningScene()->addChild(layer, 2);
        }

        return;
    }
}
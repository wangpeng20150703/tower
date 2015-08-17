//
//  Start.cpp
//  tower
//
//  Created by wangpeng on 15/8/17.
//
//

#include "Start.h"
#include "Game.h"
#include "UICallBack.h"

cocos2d::Scene* Start::createScene()
{
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();

    // 'layer' is an autorelease object
    auto layer = Start::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Start::init()
{
    if (!MyLayer::init()) {
        return false;
    }

    this->loadCsb("start/startLayer.csb");

    return true;
}

void Start::notificationHandler(Ref* pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    UICallback callback = UICallBack::getTouchUICallback(pSender);
    if (callback.enable) {
        if (callback.name.compare("onTouch") == 0) {
            if (node->getName().compare("Button_login") == 0) {
                Director::getInstance()->replaceScene(Game::createScene());
            }
            if (node->getName().compare("Button_logout") == 0) {
                //删除所有的child包括UI
                Director::getInstance()->getRunningScene()->removeAllChildren();
                Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
#endif
            }
        }
        return;
    }
}

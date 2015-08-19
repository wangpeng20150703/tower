//
//  GameOver.cpp
//  tower
//
//  Created by wangpeng on 15/8/18.
//
//

#include "GameOver.h"
#include "UICallBack.h"

#include "Game.h"

// on "init" you need to initialize your instance
bool GameOver::init()
{
    if (!MyLayer::init()) {
        return false;
    }

    this->loadCsb("restart/Layer.csb");

    return true;
}

void GameOver::notificationHandler(Ref* pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    auto name = node->getName();
    UICallback callback = UICallBack::getTouchUICallback(pSender);
    if (callback.enable) {
        if (callback.name.compare("onTouchRestart") == 0) {
            Director::getInstance()->replaceScene(Game::createScene());
            return;
        }
        return;
    }
}
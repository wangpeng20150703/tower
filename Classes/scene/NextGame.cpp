//
//  NextGame.cpp
//  tower
//
//  Created by wangpeng on 15/8/18.
//
//

#include "NextGame.h"
#include "UICallBack.h"

#include "Game.h"

// on "init" you need to initialize your instance
bool NextGame::init()
{
    if (!MyLayer::init()) {
        return false;
    }

    this->loadCsb("nextGame/Layer.csb");

    return true;
}

void NextGame::notificationHandler(Ref* pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    auto name = node->getName();
    UICallback callback = UICallBack::getTouchUICallback(pSender);
    if (callback.enable) {
        if (callback.name.compare("onTouchNextGame") == 0) {
            Game::setCurrntGame(Game::getCurrntGame() + 1);
            if (Game::getCurrntGame() == 2) {
                Game::setCurrntGame(0);
            }

            Director::getInstance()->replaceScene(Game::createScene());
            return;
        }
        return;
    }
}

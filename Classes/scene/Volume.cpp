//
//  Volume.cpp
//  tower
//
//  Created by wangpeng on 15/8/18.
//
//

#include "Volume.h"
#include "UICallBack.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Game.h"
#include "Start.h"

// on "init" you need to initialize your instance
bool Volume::init()
{
    if (!MyLayer::init()) {
        return false;
    }

    this->loadCsb("volume/Layer.csb");

    return true;
}

void Volume::notificationHandler(Ref* pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    auto name = node->getName();
    UICallback callback = UICallBack::getTouchUICallback(pSender);
    if (callback.enable) {
        if (callback.name.compare("onTouchOK") == 0) {
            this->removeFromParentAndCleanup(true);
        } else if (callback.name.compare("onTouchCancle") == 0) {
            this->removeFromParentAndCleanup(true);
        } else if (callback.name.compare("onTouchSliderVolume") == 0) {
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(
                ((Slider*)(((Node*)pSender)->getParent()->getChildByName("Slider_volume")))->getPercent() / 100.0f);
        }
    }
}
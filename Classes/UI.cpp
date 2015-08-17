//
//  UI.cpp
//  tower
//
//  Created by wangpeng on 15/8/13.
//
//

#include "UI.h"

#include "cocostudio/CocoStudio.h"

UI* UI::m_pInstance=NULL;

UI* UI::getInstance()
{
    if (!m_pInstance) {
        m_pInstance=new UI;
    }
    return m_pInstance;
}

UI::UI()
{
    CSLoader* instance = CSLoader::getInstance();
    //注意第一个参数必须是第一步填写的自定义类名加“Reader ”
    instance->registReaderObject("UICallBackReader", (ObjectFactory::Instance)UICallBackReader::getInstance);
}

void UI::onExit()
{
    Layer::onExit();
    CSLoader::destroyInstance();
    NotificationCenter::getInstance()->removeObserver(this, "end");
}

void UI::onEnter()
{
    Layer::onEnter();
}

void UI::gameover()
{
    if(auto rootNode = CSLoader::createNode("restart/Layer.csb"))
    {
        addChild((Scene*)rootNode);
    }
}

void UI::start()
{
    if(auto rootNode = CSLoader::createNode("start/startLayer.csb"))
    {
        addChild(rootNode);
    }
    
    NotificationCenter::getInstance()->addObserver(
                                                   this, CC_CALLFUNCO_SELECTOR(UI::end), "end", nullptr);
}

void UI::end(Ref* obj)
{
    //删除所有的child包括UI
    Director::getInstance()->getRunningScene()->removeAllChildren();
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void UI::nextGame()
{
    auto rootNode=CSLoader::createNode("nextGame/Layer.csb");
    if(rootNode)
    {
        addChild(rootNode);
    }
}

void UI::menu()
{
    auto rootNode=CSLoader::createNode("menu/Layer.csb");
    if (rootNode) {
        addChild(rootNode);
    }
    NotificationCenter::getInstance()->addObserver(
                                                   this, CC_CALLFUNCO_SELECTOR(UI::end), "end", nullptr);
}


//
//  Game.cpp
//  tower
//
//  Created by wangpeng on 15/7/29.
//
//

#include "Game.h"

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem =
        MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Game::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                                origin.y + closeItem->getContentSize().height / 2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //装载地图
    m_map = Map1::create();
    m_map->loadMapFile("map1.tmx");
    addChild(m_map, 1);

    scheduleUpdate();

    readInitFile();
    return true;
}

void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Game::update(float delta)
{
    if (m_vRole.empty()) {
        return;
    }
    for (int i = 0; i < m_vRole.size(); i++) {
        m_vRole[i]->run();
    }
}

void Game::makeRole(float dt)
{
    auto role = Role::create();
    addChild(role, 2);
    role->setMap(m_map->getMap());
    // m_role->getMapFileName("map1.tmx");
    role->setCurrntDirection('d');
    role->getMapPos(m_map->getMapPos());
    role->setStartPosition(Vec2(96.0f, 410.0f));  //这里的位置应该为在地图上的相对位置，即忽略地图相对屏幕的移动
    m_vRole.push_back(role);
}

void Game::readInitFile()
{
    std::string path = FileUtils::getInstance()->fullPathForFilename("role.txt");

//    float x;
//    int y;
//    x=3;
//    y=2;
//    FILE* pf1 = fopen(path.c_str(), "wb");
//    if (pf1 == NULL) {
//        CCLOG("open file error.");
//    }
//    fwrite(&x, sizeof(float), 1, pf1);
//    fwrite(&y, sizeof(int), 1, pf1);
//    fclose(pf1);
//
//    FILE* pf = fopen(path.c_str(), "rb");
//    if (pf == NULL) {
//        CCLOG("open file error.");
//    }
//     fread(&m_fIntertal, sizeof(float), 1, pf);
//         fread(&m_iCount, sizeof(int), 1, pf);
//    fclose(pf);

    m_fIntertal=3;
    m_iCount=2;
    schedule(schedule_selector(Game::makeRole), m_fIntertal, m_iCount - 1, 0);
}
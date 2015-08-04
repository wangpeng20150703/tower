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

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
    if (RoleManager::getInstance()->getRoleVector().empty()) {
        return;
    }
    for (int i = 0; i < RoleManager::getInstance()->getRoleVector().size(); i++) {
        RoleManager::getInstance()->getRoleVector()[i]->run();
    }
}

void Game::makeRole(float dt)
{
    RoleManager::getInstance()->addNewRoleToGame(ROLE1, this, 2, m_map->getMap(),'d', m_map->getMapPos(),cocos2d::Vec2(96.0f, 410.0f));
}

void Game::readInitFile()
{
    writeData();

    readData();

    schedule(schedule_selector(Game::makeRole), m_fIntertal, m_iCount - 1, 0);
}

void Game::readData()
{
    string path = FileUtils::getInstance()->fullPathForFilename("role1.txt");

    FILE* pf = fopen(path.c_str(), "rb+");
    if (pf == NULL) {
        CCLOG("open file error.");
        return;
    }
    fread(&m_fIntertal, sizeof(float), 1, pf);
    fread(&m_iCount, sizeof(int), 1, pf);
    fclose(pf);
}

void Game::writeData()
{
    string path = FileUtils::getInstance()->fullPathForFilename("role1.txt");

    float x;
    int y;
    x = 3.0f;
    y = 2;
    FILE* pf1 = fopen(path.c_str(), "wb+");
    if (pf1 == NULL) {
        CCLOG("open file error.");
        return;
    }
    fwrite(&x, sizeof(float), 1, pf1);
    fwrite(&y, sizeof(int), 1, pf1);
    fclose(pf1);
}

void Game::onTouchEnded(Touch* touch, Event* event)
{
    if (m_bIsTowerMenuExist == false) {
        Vec2 v = touch->getLocation();
        m_towerMenu = TowerMenu::create();
        addChild(m_towerMenu, 4,1);
        m_towerMenu->setPos(v, m_map->getMap(), m_map->getMap()->getPosition(),TowerManager::getInstance()->getTowerVector());
        m_bIsTowerMenuExist = true;
    } else {
        m_towerMenu->release();
        m_bIsTowerMenuExist = false;
    }
}

bool Game::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void Game::onTouchMoved(Touch* touch, Event* event)
{
}

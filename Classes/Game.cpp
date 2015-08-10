//
//  Game.cpp
//  tower
//
//  Created by wangpeng on 15/7/29.
//
//

#include "Game.h"

USING_NS_CC;
int Game::m_iCurrntGame = 0;
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

    readInitFile();

    schedule(schedule_selector(Game::makeRole), m_fIntertal, m_iCount - 1, 0);

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
    BulletManager::getInstance()->update();
    RoleManager::getInstance()->update();

    if (RoleManager::getInstance()->getDeadRole() == m_iCount) {
        BulletManager::getInstance()->release();
        RoleManager::getInstance()->release();
        TowerManager::getInstance()->release();
        unschedule(schedule_selector(Game::makeRole));

        m_iCurrntGame++;
        if (m_iCurrntGame == 2) {
            m_iCurrntGame = 0;
        }

        Scene* scene = Scene::create();
        auto layer = Game::create();
        scene->addChild(layer);
        Director::getInstance()->replaceScene(TransitionShrinkGrow::create(3.0, scene));
        this->removeFromParentAndCleanup(true);
    } else if (RoleManager::getInstance()->getSuccessRole() == 2) {
        BulletManager::getInstance()->release();
        RoleManager::getInstance()->release();
        TowerManager::getInstance()->release();
        unschedule(schedule_selector(Game::makeRole));

        Scene* scene = Scene::create();
        auto layer = Game::create();
        scene->addChild(layer);
        Director::getInstance()->replaceScene(TransitionShrinkGrow::create(3.0, scene));
        this->removeFromParentAndCleanup(true);
    }
}

void Game::makeRole(float dt)
{
    RoleManager::getInstance()->addNewRoleToGame((roleType)m_iRoleType,
                                                 this,
                                                 2,
                                                 m_map->getMap(),
                                                 m_cStartDirection,
                                                 m_map->getMapPos(),
                                                 m_vRoleStartPos,
                                                 m_vRoleEndPos);
}

void Game::readInitFile()
{
    readData();
}

void Game::readData()
{
    string path = FileUtils::getInstance()->fullPathForFilename("game.ini");

    FILE* pf = fopen(path.c_str(), "r");
    if (pf == NULL) {
        CCLOG("open file error.");
        return;
    }
    do {
        //游戏关卡
        fscanf(pf, "%d", &m_iGame);
        //角色产生延时
        fscanf(pf, "%f", &m_fIntertal);
        //角色数量
        fscanf(pf, "%d", &m_iCount);
        //角色起始位置
        fscanf(pf, "%f", &m_vRoleStartPos.x);
        fscanf(pf, "%f", &m_vRoleStartPos.y);
        //角色类型
        fscanf(pf, "%d", &m_iRoleType);
        //角色起始方向
        do {
            fscanf(pf, "%c", &m_cStartDirection);
        } while (m_cStartDirection == ' ');
        //角色终点
        fscanf(pf, "%f", &m_vRoleEndPos.x);
        fscanf(pf, "%f", &m_vRoleEndPos.y);
    } while (m_iCurrntGame != m_iGame);

    fclose(pf);

    char fileName[16];
    sprintf(fileName, "map%d.tmx", m_iGame);

    //装载地图
    m_map = Map1::create();
    m_map->loadMapFile(fileName);
    addChild(m_map, 1);

    scheduleUpdate();
}

void Game::onTouchEnded(Touch* touch, Event* event)
{
    if (m_map->getMap()->getBoundingBox().containsPoint(m_map->convertToNodeSpace(touch->getLocation()))) {
        if (m_bIsTowerMenuExist == false) {
            m_bIsTowerMenuExist = true;
            Vec2 v = touch->getLocation();
            TowerMenuManager::getInstance()->addNewTowerMenuToGame(
                this, 4, v, m_map->getMap(), m_map->getMap()->getPosition());
        } else {
            if (TowerMenuManager::getInstance()->getTowerMenu()) {
                TowerMenuManager::getInstance()->release();
            }
            m_bIsTowerMenuExist = false;
        }
    }
}

bool Game::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void Game::onTouchMoved(Touch* touch, Event* event)
{
}

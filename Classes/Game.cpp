//
//  Game.cpp
//  tower
//
//  Created by wangpeng on 15/7/29.
//
//

#include "Game.h"
#include "SimpleAudioEngine.h"

#include "NextGame.h"
#include "GameOver.h"
#include "MenuScene.h"

#include "TowerAction.h"

using namespace CocosDenshion;

USING_NS_CC;
int Game::m_iCurrntGame = 0;
int Game::m_iScore = 0;
// on "init" you need to initialize your instance

cocos2d::Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create();

    // 'layer' is an autorelease object
    auto layer = Game::create();

    layer->readData(m_iCurrntGame);
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

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

    //背景音乐加载
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/background.wav");

    NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(Game::towerAction), "towerAction", nullptr);
    NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(Game::updateScore), "scoreUpdate", nullptr);

    return true;
}

void Game::menuCloseCallback(Ref* pSender)
{
    Layer::onExit();
    auto layer = MenuScene::create();
    Director::getInstance()->getRunningScene()->addChild(layer, 1);
    NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(Game::back), "back", nullptr);
}

void Game::onExit()
{
    Layer::onExit();
    release();
    NotificationCenter::getInstance()->removeObserver(this, "back");
    NotificationCenter::getInstance()->removeObserver(this, "towerAction");
    NotificationCenter::getInstance()->removeObserver(this, "scoreUpdate");
}

void Game::back(Ref* obj)
{
    this->onEnter();
    NotificationCenter::getInstance()->removeObserver(this, "back");
}

//读取信息后创建、release后删除
void Game::update(float delta)
{
    if (RoleManager::getInstance()->getRoleVector().empty()) {
        return;
    }
    BulletManager::getInstance()->update();
    RoleManager::getInstance()->update();

    //失败
    if (RoleManager::getInstance()->getSuccessRole() == 2) {
        release();

        auto layer = GameOver::create();
        Director::getInstance()->getRunningScene()->addChild(layer, 1);

    }
    //过关
    else if (RoleManager::getInstance()->getDeadRole() + RoleManager::getInstance()->getSuccessRole() == m_iCount) {
        release();

        auto layer = NextGame::create();
        Director::getInstance()->getRunningScene()->addChild(layer, 1);
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

void Game::readData(int game)
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
        fscanf(pf, "%d", &m_iScore);
    } while (game != m_iGame);

    fclose(pf);

    char fileName[16];
    sprintf(fileName, "map%d.tmx", m_iGame);

    //装载地图
    m_map = Map1::create();
    m_map->loadMapFile(fileName);
    addChild(m_map, 1);

    scheduleUpdate();

    schedule(schedule_selector(Game::makeRole), m_fIntertal, m_iCount - 1, 0);

    SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/background.wav", true);  //播放背景音乐

    m_scoreLayer = Score::create();
    updateScore(NULL);
    addChild(m_scoreLayer, 2);
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

void Game::release()
{
    BulletManager::getInstance()->release();
    RoleManager::getInstance()->release();
    TowerManager::getInstance()->release();
    unschedule(schedule_selector(Game::makeRole));
    unscheduleUpdate();
}

int Game::getCurrntGame()
{
    return m_iCurrntGame;
}
void Game::setCurrntGame(int game)
{
    m_iCurrntGame = game;
}

void Game::towerAction(Ref* obj)
{
    TowerAction* layer = TowerAction::create();
    if (layer == NULL) {
        CCLOG("towerActionCreateError,GameTowerActionReturn");
        return;
    }
    layer->setTower((Tower*)obj);
    addChild(layer, 2);
    layer->setPosition(Vec2(((Tower*)obj)->getPos().x - 80, ((Tower*)obj)->getPos().y - 20));
}

void Game::setScore(int iScore)
{
    m_iScore = iScore;
    NotificationCenter::getInstance()->postNotification("scoreUpdate");
}
int Game::getScore()
{
    return m_iScore;
}

void Game::updateScore(Ref* ref)
{
    m_scoreLayer->setScore(m_iScore);
}

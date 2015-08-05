//
//  TowerMenu.cpp
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#include "TowerMenu.h"
#include "TowerMenuManager.h"

bool TowerMenu::init()
{
    return true;
}

void TowerMenu::onEnter()
{
    Node::onEnter();
    NotificationCenter::getInstance()->addObserver(
        this, CC_CALLFUNCO_SELECTOR(TowerMenu::addTower), "select tower", nullptr);
}
void TowerMenu::onExit()
{
    Node::onExit();
    NotificationCenter::getInstance()->removeAllObservers(this);
}

void TowerMenu::setPos(Vec2 v, cocos2d::experimental::TMXTiledMap* pMap, Vec2 mapOffset)
{
    // tile正中坐标
    int x = (v.x - mapOffset.x) / pMap->getTileSize().width;
    int y = pMap->getMapSize().height - (v.y - mapOffset.y) / pMap->getTileSize().height;
    auto layer = pMap->getLayer("layer0");
    if (layer->getTileGIDAt(Vec2(x, y)) != 3) {
        return;
    }

    v.x = ((int)((v.x - mapOffset.x) / pMap->getTileSize().width) + 0.5) * pMap->getTileSize().width;
    v.y = ((int)((v.y - mapOffset.y) / pMap->getTileSize().height) + 0.5) * pMap->getTileSize().height;
    m_vTileCenter.x = v.x + mapOffset.x;
    m_vTileCenter.y = v.y + mapOffset.y;

    //添加菜单中种类
    auto towerRed=Tower::create();
    towerRed->setTowerType(RED);
    towerRed->load("tower1.png");
    towerRed->setIsMenuTower(true);
    m_vTower.push_back(towerRed);
    auto towerYellow=Tower::create();
    towerYellow->setTowerType(YELLOW);
    towerYellow->load("tower2.png");
    towerYellow->setIsMenuTower(true);
    m_vTower.push_back(towerYellow);

    //设置子类在菜单中坐标
    m_vTower[0]->setPos(
        Vec2(v.x + mapOffset.x - m_vTower[0]->getTowerSprite()->getTextureRect().size.width, v.y + mapOffset.y));
    m_vTower[1]->setPos(
        Vec2(v.x + mapOffset.x + m_vTower[1]->getTowerSprite()->getTextureRect().size.width, v.y + mapOffset.y));
    for (int i = 0; i < m_vTower.size(); i++) {
        addChild(m_vTower[i]);
    }

    //监听
    listen();
}

void TowerMenu::addTower(Ref* obj)
{
    if (obj == NULL) {
        return;
    }
    
    if(!TowerManager::getInstance()->addNewTowerToGame(((Tower*)obj)->getTowerType(), getParent(), 1, m_vTileCenter))
    {
        log("TowerMenu::addTower ERROR");
        return;
    }
    TowerMenuManager::getInstance()->release();
}

void TowerMenu::release()
{
    this->removeFromParentAndCleanup(true);
}

void TowerMenu::listen()
{
    //设置监听
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);

    listener1->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<Tower*>(event->getCurrentTarget());

        Vec2 locationInNode = target->getTowerSprite()->convertToNodeSpace(touch->getLocation());
        Rect r = target->getTowerSprite()->getTextureRect();

        if (r.containsPoint(locationInNode)) {
            switch (target->getTowerType()) {
                case RED: {
                    auto temp = Tower::create();
                    temp->setTowerType(RED);
                    NotificationCenter::getInstance()->postNotification("select tower", temp);
                } break;
                case YELLOW: {
                    auto temp = Tower::create();
                    temp->setTowerType(YELLOW);
                    NotificationCenter::getInstance()->postNotification("select tower", temp);
                } break;
            }
            return true;
        }
        return false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, m_vTower[0]);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), m_vTower[1]);
}
//
//  TowerMenu.cpp
//  tower
//
//  Created by wangpeng on 15/7/31.
//
//

#include "TowerMenu.h"
#include "Game.h"

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
    NotificationCenter::getInstance()->removeAllObservers(this);
    Node::onExit();
}

void TowerMenu::setPos(Vec2 v, cocos2d::experimental::TMXTiledMap* pMap, Vec2 mapOffset, std::vector<Tower*> vTowerVectoer)
{
    m_vMapTower = vTowerVectoer;

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
    m_vTower.push_back(Tower1::create());
    m_vTower.push_back(Tower2::create());

    //设置子类在菜单中坐标
    m_vTower[0]->setPos(
        Vec2(v.x + mapOffset.x - m_vTower[0]->getTowerSprite()->getTextureRect().size.width, v.y + mapOffset.y));
    m_vTower[1]->setPos(
        Vec2(v.x + mapOffset.x + m_vTower[1]->getTowerSprite()->getTextureRect().size.width, v.y + mapOffset.y));
    for (int i = 0; i < m_vTower.size(); i++) {
        addChild(m_vTower[i]);
    }

    //监听
    listen(v, vTowerVectoer);
}

void TowerMenu::addTower(Ref* obj)
{
    Tower* temp;
    switch (((Tower*)obj)->getType()) {
        case RED: {
            temp = Tower1::create();
        } break;
        case YELLOW: {
            temp = Tower2::create();
        } break;
    }
    temp->setPos(m_vTileCenter);
    getParent()->addChild(temp, 1);
}

void TowerMenu::release()
{
    //    if (!m_vTower.empty()) {
    //        m_vTower[0]->getParent()->removeAllChildren();
    //    }
    //    m_vTower.clear();
    //    this->removeFromParent();
    this->removeFromParentAndCleanup(true);
}

void TowerMenu::listen(Vec2 v, std::vector<Tower*> vTowerVectoer)
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
                    temp->setType(RED);
                    NotificationCenter::getInstance()->postNotification("select tower", temp);
                } break;
                case YELLOW: {
                    auto temp = Tower::create();
                    temp->setType(YELLOW);
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
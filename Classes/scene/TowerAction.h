//
//  TowerAction.h
//  tower
//
//  Created by wangpeng on 15/8/24.
//
//

#ifndef __tower__TowerAction__
#define __tower__TowerAction__

#include <stdio.h>
#include "MyLayer.h"
#include "Tower.h"

class TowerAction : public MyLayer
{
public:
    void setTower(Tower* tower);
    virtual bool init() override;
    virtual void notificationHandler(Ref* pSender) override;
    
    CREATE_FUNC(TowerAction);
    
private:
    Tower* m_tower;
};
#endif /* defined(__tower__TowerAction__) */

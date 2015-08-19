//
//  Menu.h
//  tower
//
//  Created by wangpeng on 15/8/18.
//
//

#ifndef __tower__MenuScene__
#define __tower__MenuScene__

#include <stdio.h>
#include "MyLayer.h"

class MenuScene : public MyLayer
{
public:
    virtual bool init() override;
    virtual void notificationHandler(Ref* pSender) override;
    
    CREATE_FUNC(MenuScene);
    
private:
};

#endif /* defined(__tower__MenuScene__) */

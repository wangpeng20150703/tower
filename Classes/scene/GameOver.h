//
//  GameOver.h
//  tower
//
//  Created by wangpeng on 15/8/18.
//
//

#ifndef __tower__GameOver__
#define __tower__GameOver__

#include <stdio.h>
#include "MyLayer.h"

class GameOver : public MyLayer
{
public:
    virtual bool init() override;
    virtual void notificationHandler(Ref* pSender) override;
    
    CREATE_FUNC(GameOver);
    
private:
    std::string mode;
};

#endif /* defined(__tower__GameOver__) */

//
//  NextGame.h
//  tower
//
//  Created by wangpeng on 15/8/18.
//
//

#ifndef __tower__NextGame__
#define __tower__NextGame__

#include <stdio.h>
#include "MyLayer.h"

class NextGame : public MyLayer
{
public:
    virtual bool init() override;
    virtual void notificationHandler(Ref* pSender) override;
    
    CREATE_FUNC(NextGame);
    
private:
    std::string mode;
};

#endif /* defined(__tower__NextGame__) */

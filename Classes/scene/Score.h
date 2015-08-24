//
//  Score.h
//  tower
//
//  Created by wangpeng on 15/8/24.
//
//

#ifndef __tower__Score__
#define __tower__Score__

#include <stdio.h>
#include "MyLayer.h"

class Score : public MyLayer
{
public:
    virtual bool init() override;
    virtual void notificationHandler(Ref* pSender) override;
    
    CREATE_FUNC(Score);
    
private:
};
#endif /* defined(__tower__Score__) */

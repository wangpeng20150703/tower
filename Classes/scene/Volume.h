//
//  Volume.h
//  tower
//
//  Created by wangpeng on 15/8/18.
//
//

#ifndef __tower__Volume__
#define __tower__Volume__

#include <stdio.h>
#include "MyLayer.h"

class Volume : public MyLayer
{
public:
    virtual bool init() override;
    virtual void notificationHandler(Ref* pSender) override;
    
    CREATE_FUNC(Volume);
    
private:
};
#endif /* defined(__tower__Volume__) */

//
//  start.h
//  tower
//
//  Created by wangpeng on 15/8/17.
//
//

#ifndef __tower__start__
#define __tower__start__

#include <Stdio.h>
#include "MyLayer.h"

class Start : public MyLayer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    virtual void notificationHandler(Ref* pSender) override;
    
    void traversal(Node* node, std::string name, std::string touchName);
    
    CREATE_FUNC(Start);
    
private:
    std::string mode;
};


#endif /* defined(__tower__start__) */

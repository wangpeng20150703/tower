#ifndef __CFRAMEWORK_BASE_MyLayer_H__
#define __CFRAMEWORK_BASE_MyLayer_H__

#include "cocos2d.h"
#include "UICallBackReader.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class MyLayer : public cocos2d::Layer
{
public:
    Node* getRootNode();
    virtual bool init() override;
    virtual void onExit() override;

    virtual void notificationHandler(Ref* pSender){};
    void loadCsb(const std::string& filename);

private:
    Node* m_rootNode;
    void traversal(Node* node);
};

#endif

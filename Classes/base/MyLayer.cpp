#include "MyLayer.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio::timeline;

bool MyLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    UICallBackReader::registReaderObject();

    return true;
}

void MyLayer::onExit()
{
    NotificationCenter::getInstance()->removeAllObservers(this);

    Layer::onExit();
}

void MyLayer::loadCsb(const std::string& filename)
{
    m_rootNode = CSLoader::createNode(filename);
    
    if (NULL==m_rootNode)
    {
        log("loadCsbError");
        return;
    }
    addChild(m_rootNode, 0, filename);

    traversal(m_rootNode);
}

void MyLayer::traversal(Node* node)
{
    for (auto child : node->getChildren()) {
        UICallback callback = UICallBack::getTouchUICallback(child);
        if (callback.enable) {
            NotificationCenter::getInstance()->addObserver(
                this, callfuncO_selector(MyLayer::notificationHandler), callback.name, child);
        }

        if (child->getChildrenCount() > 0) {
            traversal(child);
        }
    }
}

Node* MyLayer::getRootNode()
{
    if (m_rootNode==NULL) {
        CCLOG("rootNodeIdNull,MyLayerGetRootNodeReturnNull");
        return NULL;
    }
    return m_rootNode;
}

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
    auto rootNode = CSLoader::createNode(filename);
    addChild(rootNode, 0, filename);

    traversal(rootNode);
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

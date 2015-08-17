//
//  UICallBackReader.h
//  cocostudio
//
//  Created by wangpeng on 15/8/12.
//
//

#ifndef __cocostudio__UICallBackReader__
#define __cocostudio__UICallBackReader__

#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

#include "UICallBack.h"

class UICallBackReader : public cocostudio::NodeReader
{
public:
    ~UICallBackReader() {};
    UICallBackReader() {};
    static UICallBackReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
    
    static void registReaderObject();
};


#endif /* defined(__cocostudio__CallBackReader__) */

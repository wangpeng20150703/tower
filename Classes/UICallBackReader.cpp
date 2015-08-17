//
//  V.cpp
//  cocostudio
//
//  Created by wangpeng on 15/8/12.
//
//

#include "UICallBackReader.h"

USING_NS_CC;

static UICallBackReader* _instanceMyClassReader = nullptr;
UICallBackReader* UICallBackReader::getInstance()
{
    if (!_instanceMyClassReader)
    {
        _instanceMyClassReader = new UICallBackReader();
    }
    return _instanceMyClassReader;
}

void UICallBackReader::purge()
{
    CC_SAFE_DELETE(_instanceMyClassReader);
}

Node* UICallBackReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    UICallBack* node = UICallBack::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}

void UICallBackReader::registReaderObject()
{
    if (_instanceMyClassReader == NULL) {
        CSLoader* instance = CSLoader::getInstance();
        //注意第一个参数必须是第一步填写的自定义类名加“Reader ”
        instance->registReaderObject("UICallBackReader", (ObjectFactory::Instance)UICallBackReader::getInstance);
    }
}
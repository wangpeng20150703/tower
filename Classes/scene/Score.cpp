//
//  Score.cpp
//  tower
//
//  Created by wangpeng on 15/8/25.
//
//

#include "Score.h"
#include "ui/UIHelper.h"

bool Score::init()
{
    if (!MyLayer::init()) {
        return false;
    }
    
    this->loadCsb("score/Layer.csb");
    
    m_scoreWidge = (TextBMFont*)Helper::seekWidgetByName((Widget*)getRootNode(), "BitmapFontLabel_score");
    
    return true;
}

void Score::setScore(int iScore)
{
    char temp[16];
    sprintf(temp,"SCORE:%d", iScore);
    if (m_scoreWidge==NULL) {
        CCLOG("scoreWidgeIsNull,ScoreSetScoreReturn");
        return;
    }
    m_scoreWidge->setString(temp);
}
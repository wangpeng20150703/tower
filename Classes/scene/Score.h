//
//  Score.h
//  tower
//
//  Created by wangpeng on 15/8/25.
//
//

#ifndef __tower__Score__
#define __tower__Score__

#include <stdio.h>
#include "MyLayer.h"
#include "ui/UITextBMFont.h"

class Score : public MyLayer
{
public:
    void setScore(int iScore);
    virtual bool init() override;
    
    CREATE_FUNC(Score);
    
private:
    TextBMFont* m_scoreWidge;
};
#endif /* defined(__tower__Score__) */

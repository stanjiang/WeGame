/**
 *  @file   MainLayer.h
 *  @brief  游戏主场景的分层
 *  @author  stanjiang
 *  @date    2018-12-12
 */


#ifndef MainLayer_h
#define MainLayer_h

#include "cocos2d.h"

class MainLayer : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
        
    CREATE_FUNC(MainLayer);
    
};




#endif /* MainLayer_h */

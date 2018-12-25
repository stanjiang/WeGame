/**
 *  @file   MainScene.h
 *  @brief  游戏主场景，游戏的入口
 *  @author  stanjiang
 *  @date    2018-12-12
 */

#ifndef MainScene_h
#define MainScene_h

#include "cocos2d.h"
#include "MainLayer.h"


class MainScene : public cocos2d::Scene
{
    
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    MainLayer* getLayer() { return _mainLayer; }
    
    CREATE_FUNC(MainScene);
 
private:
    MainLayer* _mainLayer; //

};


#endif /* MainScene_h */

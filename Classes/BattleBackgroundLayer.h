/**
 *  @file   BattleBackgroundLayer.h
 *  @brief  战斗场景的背景层，实现循环滚动背景
 *  @author  stanjiang
 *  @date    2018-12-12
 */


#ifndef BattleBackgroundLayer_h
#define BattleBackgroundLayer_h

#include "cocos2d.h"

class BattleBackgroundLayer : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
    
    virtual void update(float delta);
        
    CREATE_FUNC(BattleBackgroundLayer);
   

private:
    
    /**
     背景移动
     @param delta
     */
    void backgroundMove(float delta);

private:
    cocos2d::Sprite* _bgSprite1; // 背景精灵图1
    cocos2d::Sprite* _bgSprite2; // 背景精灵图2
    
    cocos2d::Size _visibleSize; 
    cocos2d::Vec2 _originPoint;
};




#endif /* BattleBackgroundLayer_h */

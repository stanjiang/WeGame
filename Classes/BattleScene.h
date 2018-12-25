/**
 *  @file   BattleScene.h
 *  @brief  战斗场景，这是游戏核心玩法所在的场景
 *  @author  stanjiang
 *  @date    2018-12-12
 */

#ifndef BattleScene_h
#define BattleScene_h

#include "cocos2d.h"
#include "BattleBackgroundLayer.h"
#include "HeroLayer.h"

class BattleScene : public cocos2d::Scene
{
    
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    
    CREATE_FUNC(BattleScene);
    
private:
    BattleBackgroundLayer* _bgLayer; // 战斗背景层
    HeroLayer* _heroLayer; // 玩家飞机层
};


#endif /* BattleScene_h */

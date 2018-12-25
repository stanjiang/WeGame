/**
 *  @file   Enemy.h
 *  @brief  敌机对象精灵抽象
 *  @author  stanjiang
 *  @date    2018-12-17
 */


#ifndef Enemy_h
#define Enemy_h

#include "cocos2d.h"
#include "Comm.h"

const float ENEMY_MOVE_SPEED = 100; // 敌机飞行速度，单位：pixel/sec

class Enemy
{
    
public:
    /**
     初始化精灵
     @param resFile 资源文件
     @return
     */
    bool init(const std::string resFile, int hp = ENEMY_INIT_HP_1);
    
    
    /**
     设置敌机位置
     @param pos 坐标
     */
    void setPos(const cocos2d::Vec2& pos) { _enemySprite->setPosition(pos); }
    
    
    /**
     获取敌机精灵对象
     @return 精灵对象
     */
    cocos2d::Sprite* getSprite() { return _enemySprite; }
    
    /**
     设置&获取敌机生命值
     @param hp 生命值
     */
    void setHp(int hp) { _hp = hp; }
    int getHp() { return _hp; }
    
    void setBlowupResPre(std::string resPre) { _blowupResPre = resPre; }
    
private:
    
    
    /**
     敌机爆炸处理
     */
    void blowUp();
    
private:
    cocos2d::Sprite* _enemySprite;
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _origin;
    std::string _blowupResPre; // 敌机爆炸效果的资源名前缀
    int _hp;
    
};




#endif /* Enemy_h */

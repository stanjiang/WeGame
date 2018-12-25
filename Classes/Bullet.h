/**
 *  @file   Bullet.h
 *  @brief  子弹对象精灵抽象
 *  @author  stanjiang
 *  @date    2018-12-13
 */


#ifndef Bullet_h
#define Bullet_h

#include "cocos2d.h"

const std::string RES_BULLET = "bullet1.png"; // 子弹资源图
const float BULLET_MOVE_SPEED = 100; // 子弹飞行速度，单位：pixel/sec

class Bullet
{
    
public:
    
    bool init();
    
    void setPos(const cocos2d::Vec2& pos);
    
    /**
     子弹移动 从发射位置往上 出了屏幕就应该被销毁
     @param delta
     @return
     */
    void moveBullet(float delta = 0);
    
    cocos2d::Sprite* getSprite() { return _bulletSprite; }
    
private:
    
    void bulletMoveFinished(cocos2d::Node* sender);
    
private:
    cocos2d::Sprite* _bulletSprite;
};




#endif /* Bullet_h */

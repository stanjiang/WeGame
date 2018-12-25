/**
 *  @file   HeroLayer.h
 *  @brief  主角飞机层
 *  @author  stanjiang
 *  @date    2018-12-12
 */


#ifndef HeroLayer_h
#define HeroLayer_h

#include "cocos2d.h"
#include "Bullet.h"
#include "Enemy.h"

const unsigned int HERO_TAG = 1;    // 设置玩家飞机的tag
const unsigned int RES_PATH_MAX = 256;  // 路径最大长度

class HeroLayer : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
    
    static HeroLayer* create();
    
    virtual void update(float delta);
    
    
    /**
     开始发射子弹
     @param delay 延迟时间
     */
    void startShoot(float delay = 1.0f);
    
    /**
     停止发射
     */
    void stopShoot();
    
    /**
     添加新子弹到玩家飞机层
     @param delta 子弹添加（发射）间隔时间
     @return
     */
    void addBullet(float delta);
    
    /**
     删除子弹，如：子弹和敌机碰撞时
     @param bullet 子弹对象
     */
    void removeBullet(Bullet* bullet);
    void removeBullet(cocos2d::Sprite* bullet);
    
    /**
     生成敌机
     @param delta
     */
    void addEnemy(float delta);
    
    /**
     回收敌机
     @param sender 敌机对象
     */
    void removeEnemy(cocos2d::Node* sender);
    
    /**
     敌机移动
     @param enemy 敌机对象
     */
    void moveEnemy(Enemy* enemy);
    
public:
    static HeroLayer* sharedHero; // 全局玩家飞机对象

private:
    
    /**
     根据图片创建帧动画
     @param spriteFrameVec 存储sprite frame
     */
    void createFrameAnimation(cocos2d::Vector<cocos2d::SpriteFrame*>& spriteFrameVec);

    /**
     处理一系列触摸事件
     @param touch
     @param event
     @return
     */
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    
    /**
     玩家飞机移动
     @param location 移动目标位置
     */
    void moveTo(cocos2d::Point location);
    
    /**
     碰撞检测处理
     @param contact 相关联刚体对象
     @return 碰撞结果
     */
    bool contactBegin(cocos2d::PhysicsContact& contact);
    
    /**
     创建分数板
     @return 是否成功
     */
    bool createGradeLabel();
    
    /**
     更新得分
     */
    void updateScore();
    
    /**
     处理敌机爆炸效果
     @param enemy 敌机精灵对象
     */
    void blowupEnemy(cocos2d::Sprite* enemy);
    
    /**
     预加载玩家战斗过程中所需要的音效
     */
    void PreLoadAudioEffect();
    
private:
    cocos2d::Sprite* _heroSprite; // 玩家飞机精灵
    cocos2d::Vec2 _originPoint;
    cocos2d::Size _visibleSize;
    
    cocos2d::Label* _gradeLabel; // 分数板
    int _score; // 得分

    bool _isAlive; // 玩家飞机存活标志
};




#endif /* HeroLayer_h */

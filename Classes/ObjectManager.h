/**
 *  @file   ObjectManager.h
 *  @brief  全局游戏对象管理器
 *  @author  stanjiang
 *  @date    2018-12-13
 */

#ifndef ObjectManager_h
#define ObjectManager_h

#include "cocos2d.h"
#include "Comm.h"
#include "Bullet.h"
#include "Enemy.h"

class ObjectManager
{
public:
    
    static ObjectManager * getInstance();
    static void releaseInstance();
    
    ObjectManager();
    
    
    /**
     新生成子弹至管理器
     @return return value 新生成的子弹对象
     */
    Bullet* addBullet();
    
    /**
     移除子弹对象
     @param bullet 子弹对象
     */
    void removeBullet(Bullet* bullet);
    void removeBullet(cocos2d::Sprite* bullet);
    
    
    /**
     添加敌机
     @return 敌机对象
     */
    Enemy* addEnemy();
    
    /**
     移除敌机
     @param enemy 敌机对象
     */
    void removeEnemy(cocos2d::Sprite* enemy);
    
private:
    static ObjectManager * _objMgr; // 管理器单件
    
    cocos2d::Vector<cocos2d::Sprite*> _bulletVector; // 子弹容器
    cocos2d::SpriteBatchNode* _bulletBatchNode; // 子弹批量渲染器
    
    cocos2d::Vector<cocos2d::Sprite*> _enemyVector; // 敌机容器
};


#endif /* ObjectManager_h */

#include "Enemy.h"
#include "ObjectManager.h"

USING_NS_CC;

bool Enemy::init(const std::string resFile, int hp)
{
    _enemySprite = Sprite::create(resFile);
    if (NULL == _enemySprite)
    {
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    _hp = hp; // 初始血量值
    _enemySprite->setTag(_hp); // 暂存hp，以便碰撞检测里获取
    _blowupResPre = "enemy1_down";
    
    // 设置敌机出现如随机位置
    int  x = rand()%((int)(_visibleSize.width + _origin.x) +1);
    _enemySprite->setPosition(Vec2(x, _origin.y + _visibleSize.height));
    
    // 设置刚体属性，以方便作碰撞检测
    _enemySprite->setName("enemy");
    PhysicsBody* enemyPhysicsBody = PhysicsBody::createBox(_enemySprite->getContentSize());
    enemyPhysicsBody->setGravityEnable(false); // 不受重力影响
    enemyPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
    _enemySprite->addComponent(enemyPhysicsBody);
    
    return true;
}


void Enemy::blowUp()
{
    // 创建序列帧动画 
    Animation* animation = Animation::create(); 
    std::string format = _blowupResPre + "%d.png";
    for (int i = 1; i <= 4; ++i)
    {
        
        __String* name = __String::createWithFormat(format.c_str(), i);
        animation->addSpriteFrameWithFile(name->getCString());
    }
    
    // 设置动画帧的时间间隔 
    animation->setDelayPerUnit(0.02f); 
    
    // 创建动画动作 
    Animate* animate = Animate::create(animation);
    RepeatForever* act = RepeatForever::create(animate);
    
    // 播放动画
    _enemySprite->runAction(act);
}

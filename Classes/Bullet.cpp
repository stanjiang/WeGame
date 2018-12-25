#include "Bullet.h"
#include "ObjectManager.h"

USING_NS_CC;

bool Bullet::init()
{
    _bulletSprite = Sprite::create(RES_BULLET);
    if (NULL == _bulletSprite)
    {
        return false;
    }
    
    _bulletSprite->setName("bullet");
    PhysicsBody* bulletPhysicsBody = PhysicsBody::createBox(_bulletSprite->getContentSize());
    bulletPhysicsBody->setGravityEnable(false); //不受重力影响
    bulletPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
    _bulletSprite->addComponent(bulletPhysicsBody);
    
    return true;
}

void Bullet::setPos(const cocos2d::Vec2& pos)
{
    _bulletSprite->setPosition(pos);
}

void Bullet::moveBullet(float delta)
{
    // 飞行距离，超出屏幕即结束
    float length = Director::getInstance()->getVisibleSize().height + _bulletSprite->getContentSize().height/2 - _bulletSprite->getPositionY();
    // 计算飞行时间
    float moveDuration = length / BULLET_MOVE_SPEED;
    
    FiniteTimeAction* actionMove = MoveTo::create(moveDuration, Vec2(_bulletSprite->getPositionX(), Director::getInstance()->getVisibleSize().height + _bulletSprite->getContentSize().height/2));
    FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::bulletMoveFinished, this)); // 回调一个子弹结束处理函数
    
    Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
    _bulletSprite->runAction(sequence);
}

void Bullet::bulletMoveFinished(cocos2d::Node *sender)
{
    Bullet* bullet = (Bullet*)sender;
    ObjectManager::getInstance()->removeBullet(bullet);
}

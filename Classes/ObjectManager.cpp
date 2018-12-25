#include "ObjectManager.h"
#include "HeroLayer.h"

USING_NS_CC;

ObjectManager * ObjectManager::_objMgr = NULL;

ObjectManager::ObjectManager()
{
    // SpriteBatchNode可以把相同纹理的节点在一个GL CALL里面绘制
    _bulletBatchNode = SpriteBatchNode::create(RES_BULLET);
    // 添加到玩家飞机层
    HeroLayer::sharedHero->addChild(_bulletBatchNode, 1);
}

ObjectManager * ObjectManager::getInstance()
{
    if (_objMgr == NULL)
    {
        _objMgr = new ObjectManager();
    }
    return _objMgr;
}

void ObjectManager::releaseInstance(void)
{
    if (_objMgr != NULL)
    {
        delete _objMgr;
        _objMgr = NULL;
    }
}

Bullet* ObjectManager::addBullet()
{
    Bullet* bullet = new Bullet();
    if (NULL == bullet)
    {
        return NULL;
    }
    
    if (!bullet->init())
    {
        return NULL;
    }
    
    // 添加子弹到batch中，以便批量渲染
//    _bulletBatchNode->addChild(bullet->getSprite());
    
    // 添加子弹到容器中
    _bulletVector.pushBack(bullet->getSprite());
    // 添加到玩家飞机层
    HeroLayer::sharedHero->addChild(bullet->getSprite());
    
    return bullet;
}

void ObjectManager::removeBullet(Bullet *bullet)
{
    _bulletVector.eraseObject(bullet->getSprite()); // 移除容器
    HeroLayer::sharedHero->removeChild(bullet->getSprite()); //移除屏幕
    
//    _bulletBatchNode->removeChild(bullet->getSprite(), true); //移除屏幕
}

void ObjectManager::removeBullet(cocos2d::Sprite *bullet)
{
    _bulletVector.eraseObject(bullet); // 移除容器
    HeroLayer::sharedHero->removeChild(bullet); //移除屏幕
}

Enemy* ObjectManager::addEnemy()
{
    Enemy* enemy = new Enemy();
    if (NULL == enemy)
    {
        return NULL;
    }
    
    if (!enemy->init(RES_ENEMY_1))
    {
        return NULL;
    }
    
    // 添加敌机到容器中
    _enemyVector.pushBack(enemy->getSprite());
    
    // 添加到玩家飞机层
    HeroLayer::sharedHero->addChild(enemy->getSprite());
    
    return enemy;
}

void ObjectManager::removeEnemy(Sprite* enemy)
{
    _enemyVector.eraseObject(enemy); // 移除容器
    HeroLayer::sharedHero->removeChild(enemy); //移除屏幕
}

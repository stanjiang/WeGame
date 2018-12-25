#include "HeroLayer.h"
#include "ObjectManager.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

HeroLayer* HeroLayer::sharedHero = NULL; //静态变量初始化

HeroLayer* HeroLayer::create()
{
    HeroLayer* hero = new HeroLayer();
    if (hero && hero->init())
    {
        hero->autorelease();
        sharedHero = hero; // 获得静态指针sharedHero的值
        return hero;
    }
    
    CC_SAFE_DELETE(hero);
    return NULL;
}

bool HeroLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _originPoint = Director::getInstance()->getVisibleOrigin();
    
    // 创建玩家飞机精灵
    _heroSprite = Sprite::create("hero1.png");
    if (NULL == _heroSprite)
    {
        log("get hero1 image error!");
        return false;
    }
    
    Size playSize = _heroSprite->getContentSize();
    Point playPoint = _heroSprite->getPosition();

    // 飞机放置在底部中央
    Size heroSize = _heroSprite->getContentSize();
    _heroSprite->setPosition(_visibleSize.width/2 + _originPoint.x, heroSize.height/2 + _originPoint.y);
    
    _isAlive = true; // 设置玩家飞机存活标志
    
    _heroSprite->setName("play");
    
    // 创建刚体
    PhysicsBody* playPhysicsBody = PhysicsBody::createBox(playSize);
    playPhysicsBody->setGravityEnable(false); // 不受重力影响
    playPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
    _heroSprite->addComponent(playPhysicsBody);
    
    // 设置触摸事件
    EventListenerTouchOneByOne* playListener = EventListenerTouchOneByOne::create();
    playListener->setSwallowTouches(true); // 当前层吞噬掉这个触摸，即不往优先级更低的层传送
    
    playListener->onTouchBegan=CC_CALLBACK_2(HeroLayer::touchBegan,this); // 触摸开始,必须添加
    playListener->onTouchMoved=CC_CALLBACK_2(HeroLayer::touchMoved,this); // 触摸移动
    playListener->onTouchEnded=CC_CALLBACK_2(HeroLayer::touchEnded,this); // 触摸中断，一般是系统层级的消息，如来电话，触摸事件就会被打断
    playListener->onTouchCancelled=CC_CALLBACK_2(HeroLayer::touchCancelled,this);
    
    _heroSprite->getEventDispatcher()->addEventListenerWithSceneGraphPriority(playListener, _heroSprite);
    this->addChild(_heroSprite, 1, HERO_TAG);
    
    // 预加载游戏音效
    PreLoadAudioEffect();
    
    // 默认飞机出生时，保持发射状态
    startShoot();
    
    // 添加分数板
    if (!createGradeLabel())
    {
        return false;
    }
    
    // 设置碰撞检测器
    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HeroLayer::contactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // 添加敌机
    this->schedule(SEL_SCHEDULE(&HeroLayer::addEnemy), 0.5f);
    
    return true;

    
    // 根据图片帧制作动画
//    Vector<SpriteFrame*> spriteFrameVec;
//    createFrameAnimation(spriteFrameVec);
//
//    Animation* animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1);
//    AnimationCache::getInstance()->addAnimation(animation, "animation");
//    auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("animation"));
//
//    // 闪烁动画创建与执行
//    Blink* blink = Blink::create(3.0f, 10);
//    _heroSprite->runAction(blink);
//
//    // 执行精灵帧自身动画
//    Repeat* repeat = Repeat::create(animate, 3);
//    _heroSprite->runAction(repeat);
    
}

bool HeroLayer::createGradeLabel()
{
    _gradeLabel = Label::createWithTTF("分数 : 0", "fonts/DFPShaoNvW5-GB.ttf", 14);
    
    if (NULL == _gradeLabel)
    {
        log("create grade label error!");
        return false;
    }
    
    _score = 0;
    _gradeLabel->setAnchorPoint(Vec2(0, 0));
    _gradeLabel->setPosition(Vec2(_originPoint.x, _originPoint.y + _visibleSize.height - _gradeLabel->getContentSize().height));
    this->addChild(_gradeLabel, 3);
    
    return true;
}

void HeroLayer::updateScore()
{
    ++_score;
    _gradeLabel->setString("分数 : "+ std::to_string(_score*100));
}

bool HeroLayer::contactBegin(cocos2d::PhysicsContact &contact)
{
    Node* nodeA = contact.getShapeA()->getBody()->getNode();
    Node* nodeB = contact.getShapeB()->getBody()->getNode();
    
    // 判断两者是否还存在
    if (nodeA && nodeB)
    {
        if(nodeA->getName() == "enemy" && nodeB->getName() == "bullet")
        {
            int hp = nodeA->getTag();
            if (hp > 1)
            {
                nodeA->setTag(--hp);
                log("sub current enemy ok, hp=%d", hp);
            }
            else
            {
                Sprite* enemy = static_cast<Sprite*>(nodeA);
                // 敌机爆炸处理
                blowupEnemy(enemy);
                // 更新得分
                updateScore();
            }
            
            Sprite* bullet =static_cast<Sprite*>(nodeB);
            removeBullet(bullet);

        }
        else if(nodeA->getName() == "bullet" && nodeB->getName() == "enemy")
        {
            int hp = nodeB->getTag();
            if (hp > 1)
            {
                nodeB->setTag(--hp);
                log("sub current enemy ok, hp=%d", hp);
            }
            else
            {
                Sprite* enemy = static_cast<Sprite*>(nodeB);
                // 敌机爆炸处理
                blowupEnemy(enemy);
                // 更新得分
                updateScore();
            }
            
            Sprite* bullet =static_cast<Sprite*>(nodeA);
            removeBullet(bullet);
        }
        else if(nodeA->getName() == "play" && nodeB->getName() == "enemy")
        {
            removeEnemy(nodeB);
            
            auto gameOver = GameOverScene::create();
            gameOver->setGrade(_gradeLabel->getString());
     
            Director::getInstance()->replaceScene(gameOver);
        }
        else if(nodeA->getName() == "enemy" && nodeB->getName() == "play")
        {
            removeEnemy(nodeA);
            
            auto gameOver = GameOverScene::create();
            gameOver->setGrade(_gradeLabel->getString());
            Director::getInstance()->replaceScene(gameOver);
        }
    }
    
    return false;
}

bool HeroLayer::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 pos = touch->getLocation();
    log("touchBegan x:%f,y:%f", pos.x, pos.y);
    return true;
}

void HeroLayer::touchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (_isAlive)
    {
        Sprite* target = static_cast<Sprite*>(event->getCurrentTarget()); // 获取当前的触摸目标
        Point locationInNode = target->convertToNodeSpace(touch->getLocation()); // 将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
        Size s = target->getContentSize(); // 获取精灵的文本尺寸大小
        Rect rect = Rect(0, 0, s.width, s.height); // 获取精灵的矩形框（起始点为精灵的左下角）
        
        // 允许稍微加大一点触摸位置，游戏实际需要
        rect.origin.x -= 15;
        rect.origin.y -= 15;
        rect.size.width += 30;
        rect.size.height += 30;
        
        if (rect.containsPoint(locationInNode)) // 判断触摸点是否在精灵的矩形框上
        {
           // target->setPosition(target->getPosition() + touch->getDelta()); // 将捕获的精灵坐标设在移动结束的地方
            moveTo(target->getPosition() + touch->getDelta());
        }
    }
    else
    {
      log("hero player is dead!");
    }
}

void HeroLayer::moveTo(cocos2d::Point location)
{
    // 飞机及游戏状态判断
    if(_isAlive && !Director::getInstance()->isPaused())
    {
        //进行边界判断,不可超出屏幕
        Point actualPoint;
        Size winSize = Director::getInstance()->getWinSize();
        Size planeSize = _heroSprite->getContentSize();
        if (location.x < planeSize.width/2)
        {
            location.x = planeSize.width/2;
        }
        if (location.x > (winSize.width - planeSize.width/2))
        {
            location.x = winSize.width - planeSize.width/2;
        }
        if (location.y < planeSize.height/2)
        {
            location.y = planeSize.height/2;
        }
        if (location.y > (winSize.height - planeSize.height/2))
        {
            location.y = winSize.height - planeSize.height/2;
        }
        _heroSprite->setPosition(location);
    }
}

void HeroLayer::touchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 pos = touch->getLocation();
    log("touchEnded x:%f,y:%f", pos.x, pos.y);
}


void HeroLayer::touchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{
    
}


void HeroLayer::createFrameAnimation(Vector<cocos2d::SpriteFrame*>& spriteFrameVec)
{
    SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
    
    char path[RES_PATH_MAX] = {0};
    for (int i = 1; i <=2; ++i)
    {
        sprintf(path, "hero%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(path, Rect(0, 0, 102, 126)); // 102*126是图片的大小
        spriteFrameCache->addSpriteFrame(spriteFrame, path);
        spriteFrameVec.pushBack(spriteFrame);
    }
}

void HeroLayer::startShoot(float delay)
{
    // 添加循环定时器
    this->schedule(CC_SCHEDULE_SELECTOR(HeroLayer::addBullet), 0.35f, kRepeatForever, delay);
}

void HeroLayer::stopShoot()
{
    // 卸载定时器
    this->unschedule(CC_SCHEDULE_SELECTOR(HeroLayer::addBullet));
}

void HeroLayer::addBullet(float delta)
{
    Bullet* bullet = ObjectManager::getInstance()->addBullet();
    if (NULL == bullet)
    {
        log("create bullet error!");
        return;
    }
    
    Vec2 bulletPos = Vec2(_heroSprite->getPosition().x,
                          _heroSprite->getPositionY() + _heroSprite->getContentSize().height/2 + 5);
    bullet->setPos(bulletPos);
    
    bullet->moveBullet();
}

void HeroLayer::removeBullet(Bullet *bullet)
{
    ObjectManager::getInstance()->removeBullet(bullet);
}

void HeroLayer::removeBullet(cocos2d::Sprite *bullet)
{
    ObjectManager::getInstance()->removeBullet(bullet);
}

void HeroLayer::addEnemy(float delta)
{
    Enemy* enemy = ObjectManager::getInstance()->addEnemy();
    if (NULL == enemy)
    {
        log("create enemy error!");
        return;
    }
    
    moveEnemy(enemy);
}

void HeroLayer::moveEnemy(Enemy* enemy)
{
    Sprite* enemySprite = enemy->getSprite();
    float length = _visibleSize.height + enemySprite->getContentSize().height/2; // 敌机最长飞行距离
    float moveDuration = length / ENEMY_MOVE_SPEED; // 计算飞行时间
    log("calc enemy move duration, len=%f, duration=%f", length, moveDuration);
    
    MoveTo* moveTo = MoveTo::create(moveDuration, Vec2(enemySprite->getPosition().x, 0));

    CallFuncN* funN = CallFuncN::create(CC_CALLBACK_1(HeroLayer::removeEnemy, this));
    FiniteTimeAction* moveFiniteTimeAction = Sequence::create(moveTo, funN, NULL);
    enemySprite->runAction(moveFiniteTimeAction);
}

void HeroLayer::removeEnemy(cocos2d::Node* sender)
{
    Sprite* enemy = static_cast<Sprite*>(sender);
    
    // 回收敌机对象
    ObjectManager::getInstance()->removeEnemy(enemy);
}

void HeroLayer::blowupEnemy(cocos2d::Sprite* enemy)
{
    // 创建序列帧动画 
    Animation* animation = Animation::create();
    for (int i = 1; i <= 4; ++i)
    {
        __String* name = __String::createWithFormat("enemy1_down%d.png", i);
        animation->addSpriteFrameWithFile(name->getCString());
    }
    
    // 设置动画帧的时间间隔 
    animation->setDelayPerUnit(0.02f);
    // 创建动画动作 
    Animate* animate = Animate::create(animation);
    
    // 创建序列帧动画播放结束后的回调处理
    CallFuncN* funN = CallFuncN::create(CC_CALLBACK_1(HeroLayer::removeEnemy, this));
    Sequence* actSeq = Sequence::create(animate, funN, NULL);
    
    // 播放动画
    enemy->runAction(actSeq);
    
    // 播放音效
    SimpleAudioEngine::getInstance()->playEffect("sounds/enemy1_down.wav",false);
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.8);
}

void HeroLayer::PreLoadAudioEffect()
{
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/enemy1_down.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/enemy2_down.wav");
}

void HeroLayer::update(float delta)
{

}



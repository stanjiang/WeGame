//
//  MainGameScene.cpp
//  GameDemo-mobile
//
//  Created by bnqc on 2018/9/5.
//

#include "MainGameScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainGameScene::createScene()
{
    return MainGameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool MainGameScene::init()
{
    
    if ( !Scene::init() )
    {
        return false;
    }
    
    if( !Scene::initWithPhysics() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("bg.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        Size size_back = sprite->getContentSize();
        float scaleX = (float)visibleSize.width / (float)size_back.width;
        float scaleY = (float)visibleSize.height / (float)size_back.height;
        sprite->setScale(scaleX,scaleY);
        this->addChild(sprite, 0);
    }
    
    play = Sprite::create("res/play1.png");
    if (play == nullptr) {
        problemLoading("'res/play1.png'");
    }else{
        Size playSize = play->getContentSize();
        Point playPoint = play->getPosition();
        play->setPosition(visibleSize.width/2 + origin.x, 0 + playSize.height);
        play->setName("play");
        play->setScale(1.2, 1.2);
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(4);
        animFrames.pushBack(SpriteFrame::create("res/play2.png", Rect(playPoint.x,playPoint.y,playSize.width,playSize.height)));
        animFrames.pushBack(SpriteFrame::create("res/play1.png", Rect(playPoint.x,playPoint.y,playSize.width,playSize.height)));
        animFrames.pushBack(SpriteFrame::create("res/play2.png", Rect(playPoint.x,playPoint.y,playSize.width,playSize.height)));
        animFrames.pushBack(SpriteFrame::create("res/play1.png", Rect(playPoint.x,playPoint.y,playSize.width,playSize.height)));
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        Animate* animate = Animate::create(animation);
        play->runAction(RepeatForever::create(animate));
        
        //创建刚体
        auto playPhysicsBody = PhysicsBody::createBox(playSize);
        playPhysicsBody->setGravityEnable(false);//不受重力影响
        playPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
        play->addComponent(playPhysicsBody);

        
        //设置触摸事件
        auto playListener = EventListenerTouchOneByOne::create();
        
        playListener->onTouchBegan = [](Touch* touch, Event* event){
            return true;
        };
        
        playListener->onTouchMoved = [](Touch* touch, Event* event){
            auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取当前的触摸目标
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());//将本地坐标系转化为精灵坐标系(以精灵的左下角作为坐标原点)
            Size s = target->getContentSize();//获取精灵的文本尺寸大小
            Rect rect = Rect(0, 0, s.width, s.height);//获取精灵的矩形框（起始点为精灵的左下角）
            if (rect.containsPoint(locationInNode))//判断触摸点是否在精灵的矩形框上
            {
                target->setPosition(target->getPosition() + touch->getDelta());//将捕获的精灵坐标设在移动结束的地方
            }
        };
        
        playListener->onTouchEnded = [=](Touch* touch, Event* event){

        };
        
        play->getEventDispatcher()->addEventListenerWithSceneGraphPriority(playListener, play);
        
        this->addChild(play, 1);
    }
    
    
    //添加分数板
    gradeLabel = Label::createWithTTF("分数 : 0", "fonts/PingFang Medium.ttf", 16);
    
    if (gradeLabel == nullptr)
    {
        problemLoading("'fonts/PingFang Medium.ttf'");
    }
    else
    {
        gradeLabel->setAnchorPoint(Vec2(0, 0));
        gradeLabel->setPosition(Vec2(origin.x,
                                origin.y + visibleSize.height - gradeLabel->getContentSize().height));
        this->addChild(gradeLabel, 3);
    }


    //设置碰撞检测器
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainGameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->scheduleUpdate();
    this->schedule(schedule_selector(MainGameScene::playFireAction), 0.5f);
    this->schedule(schedule_selector(MainGameScene::creatEnemySpriteAction), 0.5f);

    return true;
}

bool MainGameScene::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    //判断两者是否还存在
    if (nodeA && nodeB){
        if(nodeA->getName() == "enemy" && nodeB->getName() == "bullet"){
            this->removeChild(nodeA);
            this->removeChild(nodeB);
            grade ++;
            gradeLabel->setString("分数 : "+ std::to_string(grade*100));
        }else if(nodeA->getName() == "bullet" && nodeB->getName() == "enemy"){
            this->removeChild(nodeA);
            this->removeChild(nodeB);
            grade ++;
            gradeLabel->setString("分数 : "+ std::to_string(grade*100));
        }else if(nodeA->getName() == "play" && nodeB->getName() == "enemy"){
            auto gameOver = GameOverScene::create();
            gameOver->setGrade(gradeLabel->getString());
            Director::getInstance()->replaceScene(gameOver);
        }else if(nodeA->getName() == "enemy" && nodeB->getName() == "play"){
            auto gameOver = GameOverScene::create();
            gameOver->setGrade(gradeLabel->getString());
            Director::getInstance()->replaceScene(gameOver);
        }
    }

    //bodies can collide
    return false;
    
}


void MainGameScene::update(float delta){
    

}

void MainGameScene::creatEnemySpriteAction(float delta){
    auto enemySprite = Sprite::create("res/enemy.png");

    if (enemySprite == nullptr) {
        problemLoading("'res/enemy.png'");
    }else{
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        int  x = rand()%((int)(visibleSize.width +origin.x) +1);
        enemySprite->setPosition(Vec2(x,origin.y + visibleSize.height));
        enemySprite->setName("enemy");
        auto enemyPhysicsBody = PhysicsBody::createBox(enemySprite->getContentSize());
        enemyPhysicsBody->setGravityEnable(false);//不受重力影响
        enemyPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
        enemySprite->addComponent(enemyPhysicsBody);
        auto moveTo = MoveTo::create(3.0, Vec2(enemySprite->getPosition().x, 0));
        CallFuncN *funN=CallFuncN::create(this,callfuncN_selector(MainGameScene::removeBulletSprite));
        FiniteTimeAction *moveFiniteTimeAction = Sequence::create(moveTo,funN,NULL);
        enemySprite->runAction(moveFiniteTimeAction);
        this-> addChild(enemySprite,1);
    }
    
}

void MainGameScene::playFireAction(float delta){
    Size playSize = play->getContentSize();
    Point playPoint = play->getPosition();
    auto bulletSprite = Sprite::create("res/bullet.png");
    if (bulletSprite == nullptr) {
        problemLoading("'res/bullet.png'");
    }else{
        bulletSprite->setPosition(Vec2(playPoint.x ,playPoint.y + playSize.height/2.0 + 5));
        bulletSprite->setName("bullet");
        auto bulletPhysicsBody = PhysicsBody::createBox(bulletSprite->getContentSize());
        bulletPhysicsBody->setGravityEnable(false);//不受重力影响
        bulletPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
        bulletSprite->addComponent(bulletPhysicsBody);
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto moveTo = MoveTo::create(0.8, Vec2(bulletSprite->getPosition().x, visibleSize.height));
        CallFuncN *funN=CallFuncN::create(this,callfuncN_selector(MainGameScene::removeBulletSprite));
        FiniteTimeAction *moveFiniteTimeAction = Sequence::create(moveTo,funN,NULL);
        bulletSprite->runAction(moveFiniteTimeAction);
        this-> addChild(bulletSprite,1);
    }
}



//销毁子弹
void MainGameScene::removeBulletSprite(cocos2d::Node *bullet){
    this->removeChild(bullet);
}

void MainGameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    
}

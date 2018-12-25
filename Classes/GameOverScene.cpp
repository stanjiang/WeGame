#include "GameOverScene.h"
#include "MainScene.h"
#include "BattleScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace std;


Scene* GameOverScene::createScene()
{
    return GameOverScene::create();
}

bool GameOverScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    if( !Scene::initWithPhysics() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* sprite = Sprite::create("bg.png");
    if (NULL == sprite)
    {
        log("load res error: bg.png");
        return false;
    }
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    Size size_back = sprite->getContentSize();
    float scaleX = (float)visibleSize.width / (float)size_back.width;
    float scaleY = (float)visibleSize.height / (float)size_back.height;
    sprite->setScale(scaleX,scaleY);
    this->addChild(sprite, 0);
    
    Label* titleLabel = Label::createWithTTF("游戏结束", "fonts/PingFang Medium.ttf", 20);
    if (NULL == titleLabel)
    {
        log("load font res error: fonts/PingFang Medium.ttf");
        return false;
    }
    
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - titleLabel->getContentSize().height));
    this->addChild(titleLabel, 3);
    
    // 添加分数板
    gradeLabel = Label::createWithTTF("分数 : 0", "fonts/PingFang Medium.ttf", 16);
    
    if (gradeLabel == nullptr)
    {
        log("load font res error: fonts/PingFang Medium.ttf");
        return false;
    }
    
    gradeLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height-10-gradeLabel->getContentSize().height-titleLabel->getContentSize().height));
    this->addChild(gradeLabel, 3);

    // 添加重新开始按钮
    auto reloadGameButton = cocos2d::ui::Button::create("res/btn_bg.png");
    reloadGameButton->setTitleText("重新开始");
    reloadGameButton->setTitleFontName("fonts/PingFang Medium.ttf");
    reloadGameButton->setTitleFontSize(5);
    reloadGameButton->setScale(2, 2);
    reloadGameButton->setPosition(Vec2(origin.x + visibleSize.width/2.0, origin.y + visibleSize.height/2.0));
    reloadGameButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::BEGAN) {
            Director::getInstance()->replaceScene(BattleScene::create());
        }
    });
    this->addChild(reloadGameButton, 3);
    
    // 添加返回首页按钮
    auto gameStartSceneButton = cocos2d::ui::Button::create("res/btn_bg.png");
    gameStartSceneButton->setTitleText("返回首页");
    gameStartSceneButton->setTitleFontName("fonts/PingFang Medium.ttf");
    gameStartSceneButton->setTitleFontSize(5);
    gameStartSceneButton->setScale(2, 2);
    gameStartSceneButton->setPosition(Vec2(origin.x + visibleSize.width/2.0, origin.y + visibleSize.height/2.0 - reloadGameButton->getContentSize().height/2.0 - 10 - gameStartSceneButton->getContentSize().height));
    gameStartSceneButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::BEGAN) {
            Director::getInstance()->replaceScene(MainScene::create());
        }
    });
    this->addChild(gameStartSceneButton, 3);

    return true;
}

void GameOverScene::setGrade(std::string grade)
{
    _grade = grade;
    gradeLabel->setString(grade);
}














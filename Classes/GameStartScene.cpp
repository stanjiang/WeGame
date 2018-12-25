//
//  GameStartScene.cpp
//  GameDemo-mobile
//
//  Created by bnqc on 2018/9/5.
//
#include "GameStartScene.h"
#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
USING_NS_CC;


Scene* GameStartScene::createScene()
{
    return GameStartScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameStartScene::init()
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
    
    auto titleSprite = Sprite::create("res/start_title.png");
    if (titleSprite == nullptr)
    {
        problemLoading("'start_title.png'");
    }
    else
    {
        titleSprite->setPosition(Vec2( origin.x + visibleSize.width/2.0,
                                     origin.y + visibleSize.height - 10 - titleSprite->getContentSize().height));
        this->addChild(titleSprite, 0);
    }
    
 
    auto reloadGameButton = cocos2d::ui::Button::create("res/btn_bg.png");
    reloadGameButton->setTitleText("开始游戏");
    reloadGameButton->setTitleFontName("fonts/PingFang Medium.ttf");
    reloadGameButton->setTitleFontSize(5);
    reloadGameButton->setScale(2, 2);
    reloadGameButton->setPosition(Vec2(origin.x + visibleSize.width/2.0, origin.y + visibleSize.height/2.0));
    reloadGameButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::BEGAN) {
            Director::getInstance()->replaceScene(MainGameScene::create());
        }
    });
    this->addChild(reloadGameButton, 3);
    
    
    return true;
}

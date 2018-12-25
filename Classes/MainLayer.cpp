#include "MainLayer.h"
#include "BattleScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace std;

bool MainLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /** step1: 创建游戏背景精灵 **/
    Sprite* bgSprite = Sprite::create("bg.png");
    if (NULL == bgSprite)
    {
        log("get background image error!");
        return false;
    }
    
    bgSprite->setPosition(Vec2(size.width/2 + origin.x, size.height/2 + origin.y));
    Size sizeBack = bgSprite->getContentSize();
    float scaleX = (float)size.width / (float)sizeBack.width;
    float scaleY = (float)size.height / (float)sizeBack.height;
    bgSprite->setScale(scaleX,scaleY);
    this->addChild(bgSprite, 0);
   
    /** step2: 设置title **/    
    auto titleSprite = Sprite::create("res/start_title.png");
    if (NULL == titleSprite)
    {
        return false;
    }
    titleSprite->setPosition(Vec2( origin.x + size.width/2.0,
                                  origin.y + size.height - 10 - titleSprite->getContentSize().height));
    this->addChild(titleSprite, 0);
    
    
    /** step3: 从资源xml文件中读取中文显示出来,并创建按钮 **/
    auto dictionary = __Dictionary::createWithContentsOfFile("string.xml");
    auto startBtn = cocos2d::ui::Button::create("res/btn_bg.png");
    string text = ((__String *)(dictionary->objectForKey("play")))->getCString();
    
    startBtn->setTitleText(text);
    startBtn->setTitleFontName("fonts/PingFang Medium.ttf");
    startBtn->setTitleFontSize(5);
    startBtn->setScale(2, 2);
    startBtn->setPosition(Vec2(origin.x + size.width/2.0, origin.y + size.height/2.0));
    startBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::BEGAN) {
            Director::getInstance()->replaceScene(BattleScene::createScene());
        }
    });
    this->addChild(startBtn, 3);

    
    return true;
}


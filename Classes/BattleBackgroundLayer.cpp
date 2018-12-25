#include "BattleBackgroundLayer.h"

USING_NS_CC;
using namespace std;

bool BattleBackgroundLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _originPoint = Director::getInstance()->getVisibleOrigin();
    
    log("init battle bg layer, visiblesize=%f/%f, originpoint=%f/%f",
        _visibleSize.width, _visibleSize.height, _originPoint.x, _originPoint.y);
    
    // 创建滚动背景
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/assets_hd.plist");
    SpriteFrame* bgFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("background_2.png");
    if (NULL == bgFrame)
    {
        return false;
    }

    // load background1 sprite
    _bgSprite1 = Sprite::createWithSpriteFrame(bgFrame);
    if (NULL == _bgSprite1)
    {
        return false;
    }
    _bgSprite1->setPosition(Vec2(_visibleSize.width/2 + _originPoint.x, _visibleSize.height/2 + _originPoint.y));
    
    Size sizeBack = _bgSprite1->getContentSize();
    
    log("first bgSprite1 content size, x=%d, y=%d", (int)sizeBack.width, (int)sizeBack.height);
    
    float scaleX = (float)_visibleSize.width / (float)sizeBack.width;
    float scaleY = (float)_visibleSize.height / (float)sizeBack.height;
    _bgSprite1->setScale(scaleX,scaleY);
    
    log("last bgSprite1 content size, x=%d, y=%d", (int)sizeBack.width, (int)sizeBack.height);
    
    this->addChild(_bgSprite1, 0);
    
    // load background2 sprite
    _bgSprite2 = Sprite::createWithSpriteFrame(bgFrame);
    if (NULL == _bgSprite2)
    {
        return false;
    }
    _bgSprite2->setPosition(Vec2(_visibleSize.width/2 + _originPoint.x, _visibleSize.height + _visibleSize.height/2 + _originPoint.y));

    sizeBack = _bgSprite2->getContentSize();
    scaleX = (float)_visibleSize.width / (float)sizeBack.width;
    scaleY = (float)_visibleSize.height / (float)sizeBack.height;
    _bgSprite2->setScale(scaleX, scaleY*1.02); // 增大Y轴方向的比例，覆盖同样两张图之间的缝隙
    
    this->addChild(_bgSprite2, 0);
    
    // 执行任务计划，实现背景滚动
    this->scheduleUpdate();
    
    return true;
}

void BattleBackgroundLayer::backgroundMove(float delta)
{
    int posY1 = _bgSprite1->getPositionY();    //背景地图1的Y坐标
    int posY2 = _bgSprite2->getPositionY();    //背景地图2的Y坐标
    
    int moveSpeed = 1; //地图滚动速度
    
    // 两张地图向左滚动（两张地图是相邻的，所以要一起滚动，否则会出现空隙）
    posY1 -= moveSpeed;
    posY2 -= moveSpeed;
    
    // 获取缩放后的大小
    Rect bgRect = _bgSprite1->getBoundingBox();
    Size bgSize = bgRect.size;
    
    // 当第1个地图完全离开屏幕时，第2个地图刚好完全出现在屏幕上，这时候就让第1个地图紧贴在第2个地图后面
    if (posY1 <=  -bgSize.height / 2)
    {
        posY1 = bgSize.height + bgSize.height / 2;
    }
    // 同理，当第2个地图完全离开屏幕时，第1个地图刚好完全出现在屏幕上，这时候就让第2个地图紧贴在第1个地图后面
    if (posY2 <=  -bgSize.height / 2)
    {
        posY2 = bgSize.height + bgSize.height / 2;
    }
    
    _bgSprite1->setPositionY(posY1);
    _bgSprite2->setPositionY(posY2);
}

void BattleBackgroundLayer::update(float delta)
{
    // 背景滚动
    backgroundMove(delta);
}


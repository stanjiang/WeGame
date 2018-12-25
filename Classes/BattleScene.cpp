#include "BattleScene.h"

USING_NS_CC;

Scene* BattleScene::createScene()
{
    return BattleScene::create();
}

bool BattleScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    if( !Scene::initWithPhysics() )
    {
        return false;
    }
    
    _bgLayer = BattleBackgroundLayer::create();
    if (!_bgLayer)
    {
        return false;
    }
    // 添加背景层到战斗场景中
    this->addChild(_bgLayer);
    
    _heroLayer = HeroLayer::create();
    if (!_heroLayer)
    {
        return false;
    }
    // 添加玩家飞机层到战斗场景中
    this->addChild(_heroLayer);
    
    return true;
}

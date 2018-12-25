#include "MainScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    if( !Scene::initWithPhysics() )
    {
        return false;
    }
    
    // 预加载背景音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/game_music.mp3");
    
    _mainLayer = MainLayer::create(); // 获取MainLayer实例
    if(!_mainLayer)
    {
        return false;
    }
    this->addChild(_mainLayer);// 添加_mainLayer到主场景中
    
    // 开始播放BGM
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/game_music.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.35);
    
    return true;
}

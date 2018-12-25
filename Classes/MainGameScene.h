//
//  MainGameScene.h
//  GameDemo
//
//  Created by bnqc on 2018/9/5.
//

#ifndef MainGameScene_h
#define MainGameScene_h

#include "cocos2d.h"

class MainGameScene : public cocos2d::Scene
{
    
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();

    virtual void removeBulletSprite(cocos2d::Node *bullet);

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(MainGameScene);
    
private:
    virtual void update(float delta);
    void playFireAction(float delta);
    void creatEnemySpriteAction(float delta);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    cocos2d::Sprite *play;
    cocos2d::Label *gradeLabel;
    int grade = 0;
};

#endif

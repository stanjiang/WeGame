//
//  GameStartScene.h
//  GameDemo
//
//  Created by bnqc on 2018/9/5.
//

#ifndef GameStartScene_h
#define GameStartScene_h

#include "cocos2d.h"
using namespace std;

class GameStartScene : public cocos2d::Scene
{
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameStartScene);

};



#endif /* GameStartScene_h */

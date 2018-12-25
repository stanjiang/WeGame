/**
 *  @file   GameOverScene.h
 *  @brief  游戏结束场景
 *  @author  stanjiang
 *  @date    2018-12-18
 */

#ifndef GameOverScene_h
#define GameOverScene_h

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    
    static cocos2d::Scene* createScene();
    
    // 设置得分
    void setGrade(std::string grade);
    // 初始化
    virtual bool init();
    
    CREATE_FUNC(GameOverScene);
private:
    std::string _grade;
    cocos2d::Label * gradeLabel;
};


#endif /* GameOverScene_h */

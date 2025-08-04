#pragma once
#include "cocos2d.h"
class StartGameScene :public cocos2d::Scene
{
    static cocos2d::Scene* createScene();
    virtual bool init();

    void onLevelSelected(int level);

    CREATE_FUNC(StartGameScene);
};


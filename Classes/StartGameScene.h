#pragma once
#include "cocos2d.h"
#include "CardGameScene.h"

USING_NS_CC;

//Ñ¡Ôñ¹Ø¿¨µÄscene
class StartGameScene :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void onLevelSelected(Ref* sender);

    CREATE_FUNC(StartGameScene);
};


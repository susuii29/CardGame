#pragma once

#include "cocos2d.h"
#include "Cards.h"
#include <stack>

USING_NS_CC;
const Vec2 toposition = Vec2(700, 300);

class CardGameScene :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    //scene初始化
    virtual bool init() override;

    //为类提供一个静态create的函数
    CREATE_FUNC(CardGameScene);

private:
    std::vector<Cards*> _handCards; //存储备用牌堆
    std::vector<std::vector<Cards*>> _tableCards; //存储主牌堆
    std::vector<Cards*> _myCards; //存储底牌堆
    std::stack<std::function<void()>> _undoStack; //回退操作

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onClickTopHandCard(Cards* card);
    void onClickTableCard(Cards* card,int row);
    void onClickUndo();
};


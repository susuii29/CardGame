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
    //scene��ʼ��
    virtual bool init() override;

    //Ϊ���ṩһ����̬create�ĺ���
    CREATE_FUNC(CardGameScene);

private:
    std::vector<Cards*> _handCards; //�洢�����ƶ�
    std::vector<std::vector<Cards*>> _tableCards; //�洢���ƶ�
    std::vector<Cards*> _myCards; //�洢���ƶ�
    std::stack<std::function<void()>> _undoStack; //���˲���

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onClickTopHandCard(Cards* card);
    void onClickTableCard(Cards* card,int row);
    void onClickUndo();
};


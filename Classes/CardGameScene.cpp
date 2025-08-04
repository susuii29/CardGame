#include "CardGameScene.h"

USING_NS_CC;

int order = 1000;
int row = 2;
int column = 3;
Scene* CardGameScene::createScene() {
    return CardGameScene::create();
}

bool CardGameScene::init() {
    if (!Scene::init()) return false;

    // ���ɱ����ƶ�
    auto card1 = Cards::createCard("heart", 2);
    auto card2 = Cards::createCard("club", 4);
    card1->setPosition(200, 300);
    card2->setPosition(300, 300);
    _handCards.push_back(card1);
    _handCards.push_back(card2);
    this->addChild(card1);
    this->addChild(card2);

    // �������ƶ�
    for (int i = 0; i < row; ++i)
    {
        vector<Cards*> temp;
        for (int j = 0; j < column; ++j)
        {
            auto tableCard = Cards::createCard("diamond", j+1);
            temp.push_back(tableCard);
            tableCard->setPosition(300-j*50+300*i, 1700-j*100);
            //_tableCards[i].push_back(tableCard);
            this->addChild(tableCard);
        }
        _tableCards.push_back(temp);
    }

    // ��Ӵ����¼�
    //����¼�������������һ��ֻ����һ�������¼�
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(CardGameScene::onTouchBegan, this);
    //�¼��ַ��������¼��ַ�����Ӧ�ļ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ��ӻ��˵����ְ�ť
    auto undoBtn = MenuItemLabel::create(Label::createWithSystemFont("Undo", "Arial", 50), [=](Ref*) {
        this->onClickUndo();
        });
    auto menu = Menu::create(undoBtn, nullptr);
    menu->setPosition(1000, 500);
    this->addChild(menu);

    return true;
}

//����¼�����
bool CardGameScene::onTouchBegan(Touch* touch, Event* event) {
    Vec2 location = touch->getLocation();

    if (!_handCards.empty()) {
        auto topCard = _handCards.back();
        Vec2 nodePoint = topCard->convertToNodeSpace(location);
        Size size = topCard->getContentSize();
        Rect rect(0, 0, size.width, size.height);
        if (rect.containsPoint(nodePoint)) {
            CCLOG("������˿��ƣ�rank=%d",topCard->getRank());
            onClickTopHandCard(topCard);
            return true;
        }
    }
  
    // ��������ƣ�ֻ�����ƶ��������������Ϊ1ʱ����
        for (int i = 0; i < _tableCards.size(); ++i)
        {
            if (_tableCards[i].empty()) continue;

            auto tableCard = _tableCards[i].back();
            Vec2 nodePoint = tableCard->convertToNodeSpace(location);
            Size size = tableCard->getContentSize();
            Rect rect(0, 0, size.width, size.height);
            if (rect.containsPoint(nodePoint))
            {
                CCLOG("������˿��ƣ�rank=%d", tableCard->getRank());
                onClickTableCard(tableCard,i);
                return true;
            }
        }
    return false;
}

void CardGameScene::onClickTopHandCard(Cards* card) {
    //
    _handCards.pop_back();
    Vec2 from = card->getPosition();

    card->setLocalZOrder(order++);
    _myCards.push_back(card);
    
    card->runAction(MoveTo::create(0.3f, toposition));


    //��¼�����ƶѵĻ��˲���
    _undoStack.push([=]() {
        card->setLocalZOrder(order++);
        card->runAction(MoveTo::create(0.3f, from));
        _handCards.push_back(card);
        _myCards.pop_back();
        });
}

void CardGameScene::onClickTableCard(Cards* card,int row) {
    if (_myCards.empty()) return;

    Cards* topCard = _myCards.back();
    int diff = abs(topCard->getRank() - card->getRank());
    if (diff != 1) return;

    _tableCards[row].pop_back();
    Vec2 from = card->getPosition();

    card->setLocalZOrder(order++);
    card->runAction(MoveTo::create(0.3f, toposition));
    _myCards.push_back(card);

    //��¼������ƶѵĲ������ڻع�
    _undoStack.push([=]() {
        card->setLocalZOrder(order++);
        _myCards.pop_back();
        card->runAction(MoveTo::create(0.3f, from));
        _tableCards[row].push_back(card);
        });
}

//����undoʱ�ľ������
void CardGameScene::onClickUndo() {
    if (!_undoStack.empty()) {
        auto action = _undoStack.top();
        action();
        _undoStack.pop();
    }
}
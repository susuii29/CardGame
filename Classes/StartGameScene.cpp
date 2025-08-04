#include "StartGameScene.h"

USING_NS_CC;

Scene* StartGameScene::createScene() {
    return StartGameScene::create();
}

bool StartGameScene::init() {
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建关卡按钮
    auto level1 = MenuItemLabel::create(Label::createWithSystemFont("Level 1", "Arial", 48),CC_CALLBACK_1(StartGameScene::onLevelSelected, this));
    level1->setTag(1); // 设置关卡编号S

    auto level2 = MenuItemLabel::create(Label::createWithSystemFont("Level 2", "Arial", 48),CC_CALLBACK_1(StartGameScene::onLevelSelected, this));
    level2->setTag(2);

    auto menu = Menu::create(level1, level2, nullptr);
    menu->alignItemsVerticallyWithPadding(50);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(menu);

    return true;
}


void StartGameScene::onLevelSelected(Ref* sender) {

    auto gameScene = CardGameScene::createScene();
    Director::getInstance()->replaceScene(gameScene);
}

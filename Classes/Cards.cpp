#include "Cards.h"

Cards* Cards::createCard(const string& suit, int rank)
{
    Cards* card = new (std::nothrow) Cards();
    if (card && card->initCard(suit, rank)) {
        card->autorelease();
        return card;
    }
    CC_SAFE_DELETE(card);
    return nullptr;

}

bool Cards::initCard(const string& suit,int rank)
{
    this->_rank = rank;

	auto background = Sprite::create("card_general.png");
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Vec2(0, 0));
	this->addChild(background);

    string rankStr,color;
    if (rank == 1) rankStr = "A";
    else if (rank == 11) rankStr = "J";
    else if (rank == 12) rankStr = "Q";
    else if (rank == 13) rankStr = "K";
    else rankStr = std::to_string(rank);

    if (suit == "diamond" || suit == "heart")
    {
        color = "red";
    }
    else
    {
        color = "black";
    }

    //1、左上角小数字
    auto rankImg = Sprite::create("number/small_" + color + "_" + rankStr + ".png");
    rankImg->setAnchorPoint(Vec2(0, 1));
    rankImg->setPosition(Vec2(5, background->getContentSize().height - 10));
    background->addChild(rankImg);

    //2、中间大数字
    auto rankcenter = Sprite::create("number/big_" + color + "_" + rankStr + ".png");
    rankcenter->setAnchorPoint(Vec2(0.5,0.5));
    rankcenter->setPosition(background->getContentSize()/2);
    background->addChild(rankcenter);

    // 3. 花色图片
    auto suitImg = Sprite::create("suits/" + suit + ".png");
    suitImg->setAnchorPoint(Vec2(1, 1));
    suitImg->setPosition(Vec2(180, background->getContentSize().height - 10));
    background->addChild(suitImg);

    this->setContentSize(background->getContentSize());
    this->setAnchorPoint(Vec2(0, 0));

    return true;
}

int Cards::getRank() { return _rank; }
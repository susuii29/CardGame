#pragma once

#include "cocos2d.h"
#include<string>
using namespace std;

USING_NS_CC;

//生成不同花色的牌
class Cards : public Node
{
public:
	//获取点数
	int getRank();

	//生成一张牌
	bool initCard(const string& suit, int rank);
	static Cards* createCard(const string & suit, int rank);

private:
	int _rank; //牌点大小
};
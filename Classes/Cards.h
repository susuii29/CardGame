#pragma once

#include "cocos2d.h"
#include<string>
using namespace std;

USING_NS_CC;

//���ɲ�ͬ��ɫ����
class Cards : public Node
{
public:
	//��ȡ����
	int getRank();

	//����һ����
	bool initCard(const string& suit, int rank);
	static Cards* createCard(const string & suit, int rank);

private:
	int _rank; //�Ƶ��С
};
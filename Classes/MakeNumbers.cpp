#include "MakeNumbers.h"
#include "ImagePaths.h"
#include <string>
using namespace std;
/*
�������Ҫ����ʾ����Զ���ͼƬ���͵��˺���ֵ��
*/
MakeNumbers::MakeNumbers(int attckmun)
{
	//������ֵת��Ϊ2�и�ʽ�ַ���string��CCString��
	char char_attckmun[100] = { 0 };
	sprintf(char_attckmun, "%d", attckmun, char_attckmun);
	//�����Ҫ��;������Ϊ�ַ���int֮����໥ת��
	CCString* numberstr = CCString::create(char_attckmun);
	//���������ȡ�ַ�
	string str = numberstr->getCString();

	//��ȡ�����ز�ͼƬ��ͼƬ����Ϊ-0123456789��
	CCSprite* number_all = CCSprite::create(MAKE_NUMBER_BD);
	//��ȡ����ͼƬ����
	float allwight = number_all->getContentSize().width;
	float allhigth = number_all->getContentSize().height;
	//��ȡ����ͼƬ����
	float onewight = allwight / 11;
	float onehigth = allhigth;
	//��ȡ��һ�����ſ�Ѫ-��Ϊ����ͼƬ�ĵ�ͼ
	CCRect imgrect_moren = CCRect(0, 0, onewight, onehigth);
	numbers = CCSprite::create(MAKE_NUMBER_BD, imgrect_moren);

	//ѭ����������-�����źź���ľ�����ֵ�˺�
	for (int i = 0; i < numberstr->length(); i++)
	{
		//���ν���ÿ����ֵ��С
		string nownumber = str.substr(0 + i, 1);
		CCString* cc_nownumber = CCString::create(nownumber);
		//��������ֵȥѰ��ͼƬ
		CCRect imgrect_moren = CCRect(onewight*cc_nownumber->intValue() + onewight, 0, onewight, onehigth);
		CCSprite* numbers_now = CCSprite::create(MAKE_NUMBER_BD, imgrect_moren);
		//���õ���ͼƬ����β׷�ڡ�-��ͼƬ�ú���
		numbers_now->setPosition(ccp(numbers->getContentSize().width + numbers->getContentSize().width*i, numbers->getContentSize().height / 2));
		numbers->addChild(numbers_now, 2, 10 + i);
	}

}


MakeNumbers::~MakeNumbers(void)
{
}

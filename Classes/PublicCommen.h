#pragma once

#include "cocos2d.h"  
#include <string>
using namespace cocos2d;
using namespace std;

class PublicCommen {

public:
	/** ��ȡ�����ļ����������� */
	static string getFileByName(string pFileName);

	/** �������ݵ��ļ� */
	static bool saveFile(char* pContent, string pFileName);

	/** �����ݽ��зָ���� **/
	static std::vector<std::string> split(std::string str, std::string pattern);


};
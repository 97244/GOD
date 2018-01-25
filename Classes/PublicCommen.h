#pragma once

#include "cocos2d.h"  
#include <string>
using namespace cocos2d;
using namespace std;

class PublicCommen {

public:
	/** 读取本地文件，返回数据 */
	static string getFileByName(string pFileName);

	/** 储存内容到文件 */
	static bool saveFile(char* pContent, string pFileName);

	/** 对内容进行分割解析 **/
	static std::vector<std::string> split(std::string str, std::string pattern);


};
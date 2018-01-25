#include "PublicCommen.h"
#include "FontChina.h"
string PublicCommen::getFileByName(string pFileName) {
	//��һ�Ȼ�ȡ�ļ���·��  
	string result = "";
	//string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName; 
	string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName.c_str());

	CCLOG("path = %s", path.c_str());

	//����һ���ļ�ָ��   
	FILE* file = fopen(path.c_str(), "r");

	if (file) {
		char* buf;  //Ҫ��ȡ���ַ���  
		int len;    //��ȡ�ĳ���  
					/*��ȡ����*/
		fseek(file, 0, SEEK_END);   //�Ƶ�β��  
		len = ftell(file);          //��ȡ����  
		rewind(file);               //�ع�ԭλ  
		CCLOG("count the file content len = %d", len);
		//����buf�ռ�  
		buf = (char*)malloc(sizeof(char) * len + 1);
		if (!buf) {
			CCLOG("malloc space is not enough.");
			return NULL;
		}

		//��ȡ�ļ�  
		//��ȡ����buf����λ��С�����ȣ��ļ�ָ��  
		int rLen = fread(buf, sizeof(char), len, file);
		buf[rLen] = '\0';
		CCLOG("has read Length = %d", rLen);
		CCLOG("has read content = %s", FontChina::G2U(buf));

		result = buf;
		fclose(file);
		free(buf);
		return result;
	}
	else
	{
		result = "nofile";
	}

	return result;
}


//�ַ����ָ��
std::vector<std::string> PublicCommen::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//��չ�ַ����Է������
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}


bool PublicCommen::saveFile(char *pContent, string pFileName) {
	//��һ��ȡ������ļ�·��  
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;
	CCLOG("wanna save file path = %s", path.c_str());

	//����һ���ļ�ָ��  
	//·����ģʽ  
	FILE* file = fopen(path.c_str(), "w");
	if (file) {
		fputs(pContent, file);
		fclose(file);
	}
	else
		CCLOG("save file error.");

	return false;
}

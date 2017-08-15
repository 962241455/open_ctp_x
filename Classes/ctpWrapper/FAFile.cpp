#include "FACTPWrapper.h"

#define LOG_FILE	("openctp.log")

std::string FAFile::GetWirtePath()
{
	return FileUtils::getInstance()->getWritablePath();
}
std::string FAFile::GetResPath(char *fileName)
{
	return FileUtils::getInstance()->fullPathForFilename(fileName);
}
std::string FAFile::GetResStrBuf(char *fileName)
{
	std::string filePath = GetResPath(fileName);
	return FileUtils::getInstance()->getStringFromFile(filePath);
}

std::string  FAFile::GetResStrBuf(char *fileName, int offset)
{
	std::string filePath = GetResPath(fileName);
	Data data = FileUtils::getInstance()->getDataFromFile(filePath);
	std::string sz = std::string((const char*)data.getBytes(), offset, data.getSize());
	return sz;
}

void FAFile::Log(const char *szLog)
{
	std::string filePath = GetWirtePath() + LOG_FILE;

	FILE * p = fopen(filePath.c_str(), "at+");
	if (p)
	{
		size_t ret = fwrite(szLog, 1, strlen(szLog), p);
		fclose(p);
		if (ret != 0)
		{
			log("write log success");
		}
	}
}
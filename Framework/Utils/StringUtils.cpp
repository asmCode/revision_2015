#include "StringUtils.h"
#include <algorithm>
#include <ctype.h>

std::string StringUtils::UpperCase(const std::string &str)
{
	std::string result;
	result.resize(str.length());
	std::transform(str.begin(), str.end(), result.begin(), toupper);
	return result;
}

std::string StringUtils::LowerCase(const std::string &str)
{
	std::string result;
	result.resize(str.length());
	std::transform(str.begin(), str.end(), result.begin(), tolower);
	return result;
}

std::wstring StringUtils::ToWide(const std::string &str)
{
	return std::wstring(str.begin(), str.end());
}

std::string StringUtils::ToNarrow(const std::wstring &str)
{
	return std::string(str.begin(), str.end());
}

void StringUtils::Split(const std::string src, const std::string &separator, std::vector<std::string> &result)
{
	result.clear();

    std::string _src = src;
    int offset = 0;

    while (offset != -1)
    {
        offset = _src.find_first_of(separator);
        if (offset != -1)
        {
            result.push_back(_src.substr(0, offset));
            _src = _src.substr(offset + separator.length());
        }
    }

	result.push_back(_src);
}

float StringUtils::ParseFloat(const std::string& str)
{
	float value;
	sscanf(str.c_str(), "%f", &value);
	return value;
}

std::string StringUtils::ToString(float value)
{
	char txt[1024];
	sprintf(txt, "%f", value);
	return txt;
}

std::string StringUtils::ToString(const sm::Vec3& value)
{
	char txt[1024];
	sprintf(txt, "%f,%f,%f", value.x, value.y, value.z);
	return txt;
}

std::string StringUtils::ToString(const sm::Vec4& value)
{
	char txt[1024];
	sprintf(txt, "%f,%f,%f,%f", value.x, value.y, value.z, value.w);
	return txt;
}

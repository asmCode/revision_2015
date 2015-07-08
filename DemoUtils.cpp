#include "DemoUtils.h"
#include "../Camera.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <Utils/Random.h>
#include <Utils/StringUtils.h>
#include <stdint.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <XML/XmlWriter.h>
#include <fstream>

float DemoUtils::GetPathLength(std::vector<sm::Vec3>& path)
{
	float length = 0.0f;

	for (uint32_t i = 0; i < path.size() - 1; i++)
		length += (path[i] - path[i + 1]).GetLength();

	return length;
}

sm::Matrix DemoUtils::GetTriangleTransform(sm::Vec3* triangle)
{
	sm::Vec3 center = (triangle[0] + triangle[1] + triangle[2]) / 3.0f;

	sm::Vec3 normal = -((triangle[1] - triangle[0]) * (triangle[2] - triangle[0])).GetNormalized();
	sm::Vec3 triangleBase = triangle[1] - triangle[0];

	sm::Vec3 up = (normal * triangleBase).GetNormalized();

	sm::Matrix rotate;
	if (normal != sm::Vec3(0, 0, 0) &&
		up != sm::Vec3(0, 0, 0))
		rotate = sm::Matrix::CreateLookAt(normal, up);
	else
		rotate = sm::Matrix::Identity;

	return
		sm::Matrix::TranslateMatrix(center) *
		rotate;
}

std::string DemoUtils::ToText(const sm::Vec3& value, const std::string& separator)
{
	char text[128];
	sprintf(text, "%f%s%f%s%f", value.x, separator.c_str(), value.y, separator.c_str(), value.z, separator.c_str());
	return text;
}
std::string DemoUtils::ToText(const sm::Vec4& value, const std::string& separator)
{
	char text[128];
	sprintf(text, "%f%s%f%s%f%s%f", value.x, separator.c_str(), value.y, separator.c_str(), value.z, separator.c_str(), value.w, separator.c_str());
	return text;
}

std::string DemoUtils::ToText(const sm::Quat& value, const std::string& separator)
{
	char text[128];
	sprintf(text, "%f%s%f%s%f%s%f", value.s, separator.c_str(), value.v.x, separator.c_str(), value.v.y, separator.c_str(), value.v.z, separator.c_str());
	return text;
}

sm::Vec3 DemoUtils::ParseVector3(const std::string& vectorStr, const std::string& separator)
{
	sm::Vec3 vec;
	char mask[32];
	sprintf(mask, "%%f%s%%f%s%%f", separator.c_str(), separator.c_str(), separator.c_str());
	sscanf(vectorStr.c_str(), mask, &vec.x, &vec.y, &vec.z);
	return vec;
}

sm::Vec4 DemoUtils::ParseVector4(const std::string& vectorStr, const std::string& separator)
{
	sm::Vec4 vec;
	char mask[32];
	sprintf(mask, "%%f%s%%f%s%%f%s%%f", separator.c_str(), separator.c_str(), separator.c_str(), separator.c_str());
	sscanf(vectorStr.c_str(), mask, &vec.x, &vec.y, &vec.z, &vec.w);
	return vec;
}

void DemoUtils::ParseIntVector(const std::string& vectorStr, std::vector<int>& numbers, const std::string& separator)
{
	std::vector<std::string> numbersStr;
	StringUtils::Split(vectorStr, separator, numbersStr);
	for (uint32_t i = 0; i < numbersStr.size(); i++)
		numbers.push_back(StringUtils::ParseInt(numbersStr[i]));
}

sm::Quat DemoUtils::ParseQuat(const std::string& vectorStr, const std::string& separator)
{
	sm::Quat q;
	char mask[32];
	sprintf(mask, "%%f%s%%f%s%%f%s%%f", separator.c_str(), separator.c_str(), separator.c_str(), separator.c_str());
	sscanf(vectorStr.c_str(), mask, &q.s, &q.v.x, &q.v.y, &q.v.z);
	return q;
}

void DemoUtils::SaveCamera(Camera* camera, int slot)
{
	char camFilename[128];
	sprintf(camFilename, "cam%d", slot);
	std::ofstream camFile(camFilename);

	XmlWriter xml(&camFile, 0);

	xml.OpenElement("Camera");
	xml.OpenElement("Transform");
	xml.WriteAttribute("position", DemoUtils::ToText(camera->GetGameObject()->GetTransform().GetPosition()));
	xml.WriteAttribute("rotation", DemoUtils::ToText(camera->GetGameObject()->GetTransform().GetRotation()));
	xml.CloseElement();
	xml.CloseElement();

	camFile.close();
}

void DemoUtils::LoadCamera(Camera* camera, int slot)
{
	char camFilename[128];
	sprintf(camFilename, "cam%d", slot);

	XMLNode* root = XMLLoader::LoadFromFile(camFilename);
	if (root == NULL)
		return;

	XMLNode* transformNode = root->GetChild("Transform");
	if (transformNode == NULL)
		return;

	camera->GetGameObject()->GetTransform().SetPosition(ParseVector3(transformNode->GetAttribAsString("position")));
	camera->GetGameObject()->GetTransform().SetRotation(ParseQuat(transformNode->GetAttribAsString("rotation")));
}
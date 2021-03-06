#include "DemoUtils.h"
#include "ScenesManager.h"
#include "Scenes/BaseScene.h"
#include "../Camera.h"
#include "../GameObject.h"
#include "../Transform.h"
#include <Utils/SystemUtils.h>
#include <Utils/Random.h>
#include <Utils/StringUtils.h>
#include <Utils/Log.h>
#include <stdint.h>
#include <Math/Animation/LinearCurve.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <XML/XmlWriter.h>
#include <iomanip>
#include <fstream>
#include <sstream>

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

void DemoUtils::CopyTransformToClipboard(Transform* transform)
{
	float angle;
	sm::Vec3 axis;
	transform->GetRotation().QuatToRotate(angle, axis);

	char text[1024];
	sprintf(text, "<Transform position=\"%f, %f, %f\" rotation=\"%f, %f, %f, %f\" scale=\"%f, %f, %f\" />",
		transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z,
		angle, axis.x, axis.y, axis.z,
		transform->GetScale().x, transform->GetScale().y, transform->GetScale().z);

	SystemUtils::CopyToClipboard(text);
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

void DemoUtils::GetAllObjects(const std::string& namePrefix, std::vector<GameObject*>& gameObjects)
{
	GameObject* gameObject = NULL;

	const std::vector<GameObject*>& _gameObjects = ScenesManager::GetInstance()->GetActiveScene()->GetGameObjects();

	for (uint32_t i = 0; i < _gameObjects.size(); i++)
	{
		if (_gameObjects[i]->GetName().find(namePrefix) == 0)
			gameObjects.push_back(_gameObjects[i]);	
	}
}

void DemoUtils::GetAllChildren(const GameObject* parent, std::vector<GameObject*>& children)
{
	const std::vector<Transform*>& _children = parent->GetTransform().GetChildren();

	for (uint32_t i = 0; i < _children.size(); i++)
	{
		children.push_back(_children[i]->GetGameObject());
		GetAllChildren(_children[i]->GetGameObject(), children);
	}
}

void DemoUtils::GetAllChildrenWitchPrefix(const GameObject* parent, const std::string& namePrefix, std::vector<GameObject*>& children)
{
	std::vector<GameObject*> allChildren;
	GetAllChildren(parent, allChildren);

	for (size_t i = 0; i < allChildren.size(); i++)
	{
		if (allChildren[i]->GetName().find(namePrefix) == 0)
			children.push_back(allChildren[i]);
	}
}

void DemoUtils::NormalizeSegments(AnimationCurve<sm::Vec3>*& curve, float timeStep, float distance)
{
	const float sampleTime = 0.01f;

	AnimationCurve<sm::Vec3>* newCurve = new AnimationCurve<sm::Vec3>();

	float segmendDistance = 0.0f;
	sm::Vec3 lastPosition;
	float totalDistance = 0.0f;
	float time = 0.0f;
	for (time = curve->GetStartTime(); time <= curve->GetEndTime() + 0.00001f; time += sampleTime)
	{
		if (time == curve->GetStartTime())
		{
			lastPosition = curve->Evaluate(time);
			newCurve->AddKeyframe(time, lastPosition);
			continue;
		}

		sm::Vec3 position = curve->Evaluate(time);

		segmendDistance += (position - lastPosition).GetLength();
		totalDistance += segmendDistance;

		lastPosition = position;

		if (segmendDistance >= distance)
		{
			segmendDistance = 0.0f;

			newCurve->AddKeyframe(time, position);
		}
	}

	/*
	float lastSegDuration = newCurve->GetKeyframe(newCurve->GetKeysCount() - 1).Time - newCurve->GetKeyframe(newCurve->GetKeysCount() - 2).Time;

	float d = (curve->GetKeyframe(curve->GetKeysCount() - 1).Value - newCurve->GetKeyframe(newCurve->GetKeysCount() - 1).Value).GetLength();
	newCurve->AddKeyframe(curve->GetEndTime())
	*/

	//newCurve->AddKeyframe(time, curve->GetKeyframe(curve->GetKeysCount() - 1).Value);
	newCurve->GetKeyframe(newCurve->GetKeysCount() - 1).Time = time;
	newCurve->GetKeyframe(newCurve->GetKeysCount() - 1).Value = curve->GetKeyframe(curve->GetKeysCount() - 1).Value;

	LinearCurve<float> linear;

	float totalTime = newCurve->GetEndTime();
	for (size_t i = 0; i < newCurve->GetKeysCount(); i++)
	{
		float newmultiplier = linear.Evaluate(1.0f, 10, newCurve->GetKeyframe(i).Time / totalTime);
		newCurve->GetKeyframe(i).Time *= newmultiplier;

		Log::LogT("multiplier = %f, time = %f", newmultiplier, newCurve->GetKeyframe(i).Time);
	}

	delete curve;
	curve = newCurve;
	curve->SmoothTangents();
}

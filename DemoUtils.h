#pragma once

#include "GameObject.h"
#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <Math/Animation/AnimationCurve.h>
#include <vector>

class Camera;

class DemoUtils
{
public:
	static float GetPathLength(std::vector<sm::Vec3>& path);
	static sm::Matrix GetTriangleTransform(sm::Vec3* triangle);
	static std::string ToText(const sm::Vec3& value, const std::string& separator = ";");
	static std::string ToText(const sm::Vec4& value, const std::string& separator = ";");
	static std::string ToText(const sm::Quat& value, const std::string& separator = ";");
	static sm::Vec3 ParseVector3(const std::string& vectorStr, const std::string& separator = ";");
	static sm::Vec4 ParseVector4(const std::string& vectorStr, const std::string& separator = ";");
	static void ParseIntVector(const std::string& vectorStr, std::vector<int>& numbers, const std::string& separator = ";");
	static sm::Quat ParseQuat(const std::string& vectorStr, const std::string& separator = ";");
	static void SaveCamera(Camera* camera, int slot);
	static void LoadCamera(Camera* camera, int slot);
	static void CopyTransformToClipboard(Transform* transform);
	static void GetAllObjects(const std::string& namePrefix, std::vector<GameObject*>& gameObjects);
	static void GetAllChildren(const GameObject* parent, std::vector<GameObject*>& children);
	static void GetAllChildrenWitchPrefix(const GameObject* parent, const std::string& namePrefix, std::vector<GameObject*>& children);
	template <typename T>
	static void AttachComponentBunch(
		const std::string& namePrefix,
		const std::string& componentName,
		std::vector<T*>& components)
	{
		std::vector<GameObject*> gameObjects;
		GetAllObjects(namePrefix, gameObjects);

		for (uint32_t i = 0; i < gameObjects.size(); i++)
		{
			T* component = (T*)gameObjects[i]->AddComponent(componentName);
			assert(component != NULL);

			components.push_back(component);
		}
	}

	template <typename T>
	static void AttachComponentBunch(
		const std::string& componentName,
		std::vector<GameObject*>& gameObjects,
		std::vector<T*>& components)
	{
		for (uint32_t i = 0; i < gameObjects.size(); i++)
		{
			T* component = (T*)gameObjects[i]->AddComponent(componentName);
			assert(component != NULL);

			components.push_back(component);
		}
	}

	template <typename T>
	static void GetAllGameObjectsAsComponent(const std::string& namePrefix, const std::string& componentName, std::vector<T*>& components)
	{
		std::vector<GameObject*> gameObjects;
		GetAllObjects(namePrefix, gameObjects);

		for (uint32_t i = 0; i < gameObjects.size(); i++)
		{
			components.push_back(dynamic_cast<T*>(gameObjects[i]->GetComponent(componentName)));
		}
	}

	static void NormalizeSegments(AnimationCurve<sm::Vec3>*& curve, float timeStep, float distance);

	static bool StepTo(float& from, const float& to, float step)
	{
		if (from == to)
			return true;

		float dir = to - from;
		if (step >= dir)
		{
			from = to;
			return true;
		}

		from += step;
		return false;
	}

	static bool StepTo(sm::Vec3& from, const sm::Vec3& to, float step)
	{
		if (from == to)
			return true;

		sm::Vec3 dir = to - from;
		if (step >= dir.GetLength())
		{
			from = to;
			return true;
		}

		from += dir.GetNormalized() * step;
		return false;
	}

	static bool StepTo(sm::Quat& from, const sm::Quat& to, float step)
	{
		if (from == to)
			return true;

		sm::Quat dir = to - from;
		if (step >= dir.GetLength())
		{
			from = to;
			return true;
		}

		from = from + dir.GetNormalized() * step;
		from.Normalize();
		return false;
	}
};

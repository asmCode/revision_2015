#include "AnimationClipLoader.h"
#include "AnimationClip.h"
#include "PropertyAnimationData.h"
#include <Utils/StringUtils.h>
#include "../DemoUtils.h"
#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <Math/Quat.h>
#include <Math/Animation/AnimationCurve.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>

AnimationClip* AnimationClipLoader::LoadFromFile(const std::string& filename)
{
	XMLNode* rootNode = XMLLoader::LoadFromFile(filename);
	if (rootNode == NULL)
		return NULL;

	if (rootNode->GetName() != "AnimationClip")
	{
		delete rootNode;
		return NULL;
	}

	AnimationClip* animClip = new AnimationClip(rootNode->GetAttribAsString("name"));

	for (uint32_t i = 0; i < rootNode->GetChildrenCount(); i++)
	{
		XMLNode* animNode = rootNode->GetChild(i);
		if (animNode->GetName() != "Anim")
			continue;

		PropertyAnimationData* propAnimData = LoadPropertyAnimation(animNode);
		if (propAnimData == NULL)
			continue;

		animClip->AddPropertyAnimation(propAnimData);
	}

	return animClip;
}

PropertyAnimationData* AnimationClipLoader::LoadPropertyAnimation(XMLNode* propAnimNode)
{
	if (propAnimNode == NULL)
		return NULL;

	PropertyType type = ParseParamType(propAnimNode->GetAttribAsString("type"));
	std::string target = propAnimNode->GetAttribAsString("target");
	std::string component = propAnimNode->GetAttribAsString("component");
	std::string property = propAnimNode->GetAttribAsString("property");

	void* animationCurve = NULL;

	switch (type)
	{
	case PropertyType_Float:
		animationCurve = new AnimationCurve<float>();
		break;
	case PropertyType_Int:
		animationCurve = new AnimationCurve<int>();
		break;
	case PropertyType_Vec3:
		animationCurve = new AnimationCurve<sm::Vec3>();
		break;
	case PropertyType_Quat:
		animationCurve = new AnimationCurve<sm::Quat>();
		break;
	}

	for (uint32_t i = 0; i < propAnimNode->GetChildrenCount(); i++)
	{
		XMLNode* keyNode = propAnimNode->GetChild(i);
		if (keyNode->GetName() != "Key")
			continue;

		float time = keyNode->GetAttribAsFloat("t");
		std::string value = keyNode->GetAttribAsString("v");

		switch (type)
		{
		case PropertyType_Float:
			((AnimationCurve<float>*)animationCurve)->AddKeyframe(time, StringUtils::ParseFloat(value));
			break;
		case PropertyType_Int:
			((AnimationCurve<int>*)animationCurve)->AddKeyframe(time, StringUtils::ParseInt(value));
			break;
		case PropertyType_Vec3:
			((AnimationCurve<sm::Vec3>*)animationCurve)->AddKeyframe(time, DemoUtils::ParseVector3(value, ","));
			break;
		case PropertyType_Quat:
			{
				sm::Vec4 vec4 = DemoUtils::ParseVector4(value, ",");
				sm::Quat quat = sm::Quat::FromAngleAxis(vec4.x, sm::Vec3(vec4.y, vec4.w, -vec4.z));	
				((AnimationCurve<sm::Quat>*)animationCurve)->AddKeyframe(time, quat);
			}
			break;
		}
	}

	switch (type)
	{
	case PropertyType_Float:
		((AnimationCurve<float>*)animationCurve)->SmoothTangents();
		break;
	case PropertyType_Int:
		((AnimationCurve<int>*)animationCurve)->SmoothTangents();
		break;
	case PropertyType_Vec3:
		((AnimationCurve<sm::Vec3>*)animationCurve)->SmoothTangents();
		break;
	case PropertyType_Quat:
		((AnimationCurve<sm::Quat>*)animationCurve)->SmoothTangents();
		break;
	}

	return new PropertyAnimationData(type, target, component, property, animationCurve);
}

PropertyType AnimationClipLoader::ParseParamType(const std::string& paramTypeText)
{
	if (paramTypeText == "float")
		return PropertyType_Float;
	if (paramTypeText == "int")
		return PropertyType_Int;
	if (paramTypeText == "vec3")
		return PropertyType_Vec3;
	if (paramTypeText == "quat")
		return PropertyType_Quat;

	return PropertyType_Float;
}

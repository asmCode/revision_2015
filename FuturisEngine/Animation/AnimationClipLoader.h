#pragma once

#include "../PropertyType.h"
#include <string>

class AnimationClip;
class PropertyAnimationData;
class XMLNode;

class AnimationClipLoader
{
public:
	static AnimationClip* LoadFromFile(const std::string& filename);

private:
	static PropertyAnimationData* LoadPropertyAnimation(XMLNode* propAnimNode);

	static PropertyType ParseParamType(const std::string& paramTypeText);
};

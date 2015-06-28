#pragma once

#include "../../Parameter.h"
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

	static Parameter::Type ParseParamType(const std::string& paramTypeText);
};

#pragma once

#include <vector>

class AnimationClip;
class GameObject;
class AnimationPropertyAttachement;

class AnimationClipAttachement
{
public:
	AnimationClipAttachement(
		AnimationClip* animationClip,
		GameObject* gameObject);

	~AnimationClipAttachement();

	void SetTime(float time);

private:
	AnimationClip* m_animationClip;
	GameObject* m_gameObject;

	std::vector<AnimationPropertyAttachement*> m_attachements;
};

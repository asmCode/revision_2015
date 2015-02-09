#pragma once

#include <string>

namespace SceneElement
{
	class Material;

	class CustomSceneElement
	{
	public:
		CustomSceneElement();

		std::string Type;
		std::string Id;
		std::string MeshName;
		Material* Material;
	};
}

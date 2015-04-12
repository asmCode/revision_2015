#include "Content.h"

#include "../IGraphicsEngine.h"
#include "../Material.h"
#include "../Model.h"
#include "../SkinnedMeshLoader.h"
#include <IO/Path.h>

Content* Content::Instance;

Content::Content(IGraphicsEngine *graphicsEngine) :
	m_graphicsEngine(graphicsEngine)
{
	Instance = this;
}

Content::~Content()
{

}

void Content::LoadTextures(const std::string &fullPath)
{
	std::vector<std::string> filesNames;
	Path::GetAllFiles(filesNames, fullPath, "*.png");
	Path::GetAllFiles(filesNames, fullPath, "*.jpg");

	for (uint32_t i = 0 ; i < filesNames.size(); i++)
	{
		Path path(fullPath + filesNames[i]);

		m_textures[path.GetFilename()] = m_graphicsEngine->LoadTexture(path.GetFullPath());
	}
}

void Content::LoadShaders(const std::string &fullPath)
{
	std::vector<std::string> filesNames;
	Path::GetAllFiles(filesNames, fullPath, "*.vpr");

	for (uint32_t i = 0 ; i < filesNames.size(); i++)
	{
		// all vertex programs must have corresponding fragment program
		Path vprPath(fullPath + filesNames[i]);
		Path fprPath(fullPath + vprPath.GetFilename() + ".fpr");

		m_shaders[vprPath.GetFilename()] = m_graphicsEngine->LoadShader(vprPath.GetFullPath(), fprPath.GetFullPath());
	}
}

void Content::LoadModels(const std::string &fullPath)
{
	std::vector<std::string> filesNames;
	Path::GetAllFiles(filesNames, fullPath, "*.geo");

	for (uint32_t i = 0 ; i < filesNames.size(); i++)
	{
		Path path(fullPath + filesNames[i]);

		m_models[path.GetFilename()] = m_graphicsEngine->LoadModel(path.GetFullPath());
	}
}

void Content::LoadAnimations(const std::string &fullPath)
{
	std::vector<std::string> filesNames;
	Path::GetAllFiles(filesNames, fullPath, "*.ani");

	for (uint32_t i = 0 ; i < filesNames.size(); i++)
	{
		Path path(fullPath + filesNames[i]);

		m_animations[path.GetFilename()] = m_graphicsEngine->LoadAnimation(path.GetFullPath());
	}
}

/*
void Content::LoadMaterials(const std::string &fullPath)
{
	std::vector<std::string> filesNames;
	Path::GetAllFiles(filesNames, fullPath, "*.mat");

	for (uint32_t i = 0 ; i < filesNames.size(); i++)
	{
		Path path(fullPath + filesNames[i]);

		m_materials[path.GetFilename()] = m_graphicsEngine->LoadMaterial(path.GetFullPath());
	}
}
*/

void Content::LoadSkinnedMeshes(const std::string &fullPath)
{
	std::vector<std::string> filesNames;
	Path::GetAllFiles(filesNames, fullPath, "*.skm");

	for (uint32_t i = 0; i < filesNames.size(); i++)
	{
		Path path(fullPath + filesNames[i]);

		m_skinnedMeshes[path.GetFilename()] = SkinnedMeshLoader::LoadFromFile(path.GetFullPath());
	}
}


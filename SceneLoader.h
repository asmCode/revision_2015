#pragma once

#include <string>
#include <vector>
#include <map>

class GameObject;
class Ribbon;
class Guy;
class Static;
class BaseScene;
class Material;
class Parameter;

namespace SceneElement
{
	class Path;
	class Key;
	class IntKey;
	class FloatKey;
	class StaticData;
	class GuyData;
	class CustomSceneElement;
}

class XMLNode;

class SceneLoader
{
public:
	bool LoadFromFile(BaseScene* scene, const std::string& sceneName);

	// Doladowuje dane ze sceny z innego pliku xml.
	bool LoadAdditive(const std::string& filename);
	void BuildScene(BaseScene* baseScene);

private:
	class Object
	{
	public:
		Object(XMLNode* xmlNode, const std::string& sceneName) :
			XMLNode(xmlNode),
			SceneName(sceneName)
		{
		}

		XMLNode* XMLNode;
		std::string SceneName;
	};

	BaseScene* m_loadingScene;

	std::map<std::string, Material*> m_materials;

	SceneElement::Path* LoadPath(XMLNode* node);
	SceneElement::Key* LoadKey(XMLNode* node);
	SceneElement::GuyData* LoadGuy(XMLNode* node);
	Material* LoadMaterial(XMLNode* materialNode);
	SceneElement::CustomSceneElement* LoadCustomSceneElement(XMLNode* elementNode);
	static void LoadIntKeys(XMLNode* node, std::vector<SceneElement::IntKey*>& keys);
	static void LoadFloatKeys(XMLNode* node, std::vector<SceneElement::FloatKey*>& keys);

	Guy* CreateGuyFromData(const std::string& sceneName, SceneElement::GuyData* guyData);
	GameObject* CreateElementFromData(const std::string& sceneName, SceneElement::CustomSceneElement* data);

	void LoadGameObjects(const std::string& sceneName, XMLNode* node);
	GameObject* LoadGameObject(const std::string& sceneName, XMLNode* node);

	Material* FindMaterial(const std::string& materialName);

	void LoadParameters(XMLNode* parentNode, std::vector<Parameter>& parameters);
	Parameter LoadParameter(XMLNode* parameterNode);

	std::vector<Object> m_materialNodes;
	std::vector<Object> m_gameObjectNodes;
};


#pragma once

#include <string>
#include <vector>
#include <map>

class GameObject;
class BaseScene;
class Material;
class Parameter;
class Transform;

namespace SceneElement
{
	class Path;
	class Key;
	class IntKey;
	class FloatKey;
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

	class Node
	{
	public:
		Node(const std::string& name) :
			Name(name),
			Parent(NULL)
		{ }

		std::string Name;
		Node* Parent;
		std::vector<Node*> Children;
	};

	BaseScene* m_loadingScene;

	std::map<std::string, Material*> m_materials;
	std::vector<Node*> m_hierarchyRootNodes;

	SceneElement::Path* LoadPath(XMLNode* node);
	SceneElement::Key* LoadKey(XMLNode* node);
	Material* LoadMaterial(XMLNode* materialNode);
	SceneElement::CustomSceneElement* LoadCustomSceneElement(XMLNode* elementNode);
	static void LoadIntKeys(XMLNode* node, std::vector<SceneElement::IntKey*>& keys);
	static void LoadFloatKeys(XMLNode* node, std::vector<SceneElement::FloatKey*>& keys);

	GameObject* CreateElementFromData(const std::string& sceneName, SceneElement::CustomSceneElement* data);

	void LoadGameObjects(const std::string& sceneName, XMLNode* node);
	GameObject* LoadGameObject(const std::string& sceneName, XMLNode* node);

	Material* FindMaterial(const std::string& materialName);

	void LoadParameters(XMLNode* parentNode, std::vector<Parameter>& parameters);
	Parameter LoadParameter(XMLNode* parameterNode);

	std::vector<Object> m_materialNodes;
	std::vector<Object> m_gameObjectNodes;

	void LoadHierarchy(XMLNode* hierarchyNode);
	Node* LoadHierarchyNode(XMLNode* node);
	void SetGameObjectTransformHierarchy(SceneLoader::Node* node, Transform* parent);
};


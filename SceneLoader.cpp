#include "SceneLoader.h"
#include "Environment.h"
#include "GameObject.h"
#include "DemoUtils.h"
#include "ScenesManager.h"
#include "Scenes/BaseScene.h"
#include "../Renderable.h"
#include "DemoController.h"
#include "FuturisEngine/BehavioursManager.h"
#include "Behaviour.h"

#include "SceneElement/Path.h"
#include "SceneElement/Key.h"
#include "SceneElement/IntKey.h"
#include "SceneElement/FloatKey.h"
#include "SceneElement/Material.h"
#include "SceneElement/CustomSceneElement.h"

#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <Graphics/Model.h>
#include <Graphics/Material.h>
#include <Graphics/Shader.h>
#include "Light.h"
#include "Camera.h"
#include "../FuturisEngine/Graphics/Mesh.h"


#include <IO/Path.h>
#include <Utils/StringUtils.h>

#include <XML/XMLNode.h>
#include <XML/XMLLoader.h>

#include "./Utils/Stopwatch.h"
#include <Utils/Log.h>

#include <map>

#include "Parameter.h"

using namespace FuturisEngine::Graphics;

bool SceneLoader::LoadFromFile(BaseScene* scene, const std::string& sceneName)
{
	m_loadingScene = scene;

	Log::LogT("Loading scene %s ===================================", sceneName.c_str());

	Stopwatch stopwatch(true);

	std::string path = Environment::GetInstance()->GetBasePath() + "Scenes\\" + sceneName + ".scene";

	XMLNode* rootNode = XMLLoader::LoadFromFile(path);
	if (rootNode == NULL)
		return false;

	Log::LogT("Loading xml time: %.2f", stopwatch.GetTime());

	scene->m_name = rootNode->GetAttribAsString("name");

	for (uint32_t rootIndex = 0; rootIndex < rootNode->GetChildrenCount(); rootIndex++)
	{
		XMLNode* node = rootNode->GetChild(rootIndex);
		if (node == NULL)
			continue;

		if (node->GetName() == "IncludeScene")
		{

		}
		else if (node->GetName() == "Materials")
		{
			stopwatch.ResetAndStart();

			for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
			{
				Material* material = LoadMaterial(node->GetChild(i));
				if (material != NULL)
				{
					m_materials[material->GetName()] = material;
					Content::Instance->Add(material->GetName(), material);
				}
			}

			Log::LogT("Loading materials time: %.2f", stopwatch.GetTime());
		}
		else if (node->GetName() == "GameObjects")
		{
			stopwatch.ResetAndStart();

			LoadGameObjects(sceneName, node);

			Log::LogT("Loading GameObjects time: %.2f", stopwatch.GetTime());
		}
	}

	return true;

	Log::LogT("Loading ribbons time: %.2f", stopwatch.GetTime());
	stopwatch.ResetAndStart();

	/*
	XMLNode* staticMeshesNode = node->GetChild("StaticMeshes");
	if (staticMeshesNode != NULL)
	{
		for (uint32_t i = 0; i < staticMeshesNode->GetChildrenCount(); i++)
		{
			SceneElement::StaticData* staticData = LoadStatic(staticMeshesNode->GetChild(i));
			if (staticData == NULL)
				continue;
		}
	}
	*/
	/*
	Log::LogT("Loading static time: %.2f", stopwatch.GetTime());
	stopwatch.ResetAndStart();

	XMLNode* guysNode = node->GetChild("Guys");
	if (guysNode != NULL)
	{
		for (uint32_t i = 0; i < guysNode->GetChildrenCount(); i++)
		{
			SceneElement::GuyData* guyData = LoadGuy(guysNode->GetChild(i));
			if (guyData == NULL)
				continue;

			Guy* guy = CreateGuyFromData(scene->m_name, guyData);
			if (guy != NULL)
				scene->m_gameObjects.push_back(guy);
		}
	}

	Log::LogT("Loading guys time: %.2f", stopwatch.GetTime());
	stopwatch.ResetAndStart();

	XMLNode* elementsNode = node->GetChild("Elements");
	if (elementsNode != NULL)
	{
		for (uint32_t i = 0; i < elementsNode->GetChildrenCount(); i++)
		{
			SceneElement::CustomSceneElement* data = LoadCustomSceneElement(elementsNode->GetChild(i));
			if (data == NULL)
				continue;

			GameObject* element = CreateElementFromData(scene->m_name, data);
			if (element != NULL)
				scene->m_gameObjects.push_back(element);
		}
	}

	return true;
	*/
}

SceneElement::Path* SceneLoader::LoadPath(XMLNode* node)
{
	SceneElement::Path* path = new SceneElement::Path();

	path->Spread = node->GetAttribAsFloat("spread", 1.0f);
	path->TriangleScale = node->GetAttribAsFloat("triangle_scale", 0.5f);
	path->Delay = node->GetAttribAsFloat("delay", 4.0f);
	path->DontRender = node->GetAttribAsBool("dont_render", false);

	XMLNode* ribbonWeightsNode = node->GetChild("RibbonWeights");
	if (ribbonWeightsNode != NULL)
		LoadFloatKeys(ribbonWeightsNode, path->RibbonWeights);

	for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
	{
		if (node->GetChild(i)->GetName() != "Key")
			continue;

		SceneElement::Key *key = LoadKey(node->GetChild(i));
		if (key != NULL)
			path->Keys.push_back(key);
	}

	return path;
}

SceneElement::Key* SceneLoader::LoadKey(XMLNode* node)
{
	SceneElement::Key* key = new SceneElement::Key();

	key->Time = node->GetAttribAsFloat("time");
	key->Position = DemoUtils::ParseVector3(node->GetAttribAsString("position"));
	key->Rotation.Set(0.0f, 1.0f, 0.0f, 0.0f);
	key->Scale.Set(1.0f, 1.0f, 1.0f);

	return key;
}

SceneElement::CustomSceneElement* SceneLoader::LoadCustomSceneElement(XMLNode* elementNode)
{
	SceneElement::CustomSceneElement* data = new SceneElement::CustomSceneElement();
	data->Type = elementNode->GetName();
	data->Id = elementNode->GetAttribAsString("id");
	data->MeshName = elementNode->GetAttribAsString("mesh_name");

	return data;
}

Material* SceneLoader::LoadMaterial(XMLNode* materialNode)
{
	assert(materialNode->GetName() == "Material");

	Material* material = new Material();

	std::string shaderName = materialNode->GetAttribAsString("shader");

	Shader* shader = Content::Instance->Get<Shader>(shaderName);
	if (shader == NULL)
		return NULL;

	material->name = materialNode->GetAttribAsString("name");
	material->SetShader(shader);
	
	XMLNode* parametersNode = materialNode->GetChild("Parameters");
	if (parametersNode != NULL)
	{
		for (uint32_t i = 0; i < parametersNode->GetChildrenCount(); i++)
		{
			Parameter parameter = LoadParameter(parametersNode->GetChild(i));

			switch (parameter.GetType())
			{
			case Parameter::Type_Float:
				material->SetParameter(parameter.GetName(), parameter.GetFloat());
				break;

			case Parameter::Type_Vec3:
				material->SetParameter(parameter.GetName(), parameter.GetVec3());
				break;

			case Parameter::Type_Vec4:
				material->SetParameter(parameter.GetName(), parameter.GetVec4());
				break;

			case Parameter::Type_Texture:
				material->SetParameter(parameter.GetName(), parameter.GetTexture());
				break;
			}
		}
	}

	return material;
}

void SceneLoader::LoadIntKeys(XMLNode* node, std::vector<SceneElement::IntKey*>& keys)
{
	for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
	{
		SceneElement::IntKey* key = new SceneElement::IntKey();
		key->Time = node->GetChild(i)->GetAttribAsFloat("time");
		key->Value = node->GetChild(i)->GetAttribAsInt32("value");

		keys.push_back(key);
	}
}

void SceneLoader::LoadFloatKeys(XMLNode* node, std::vector<SceneElement::FloatKey*>& keys)
{
	for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
	{
		if (node->GetChild(i)->GetName() != "Key")
			continue;

		SceneElement::FloatKey* key = new SceneElement::FloatKey();
		key->Time = node->GetChild(i)->GetAttribAsFloat("time");
		key->Value = node->GetChild(i)->GetAttribAsFloat("value");

		keys.push_back(key);
	}
}

/*Guy* SceneLoader::CreateGuyFromData(const std::string& sceneName, SceneElement::GuyData* guyData)
{
	return new Guy(sceneName, guyData);
}*/

/*
GameObject* SceneLoader::CreateElementFromData(const std::string& sceneName, SceneElement::CustomSceneElement* data)
{
	if (data->Type == "BlinkStatic")
		return new BlinkStatic(sceneName, data);

	return NULL;
}
*/

Material* SceneLoader::FindMaterial(const std::string& materialName)
{
	std::map<std::string, Material*>::iterator it = m_materials.find(materialName);
	if (it == m_materials.end())
		return NULL;

	return it->second;
}

void SceneLoader::LoadGameObjects(const std::string& sceneName, XMLNode* node)
{
	if (node == NULL)
		return;

	for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
	{
		GameObject* gameObject = LoadGameObject(sceneName, node->GetChild(i));
		if (gameObject != NULL)
			m_loadingScene->m_gameObjects.push_back(gameObject);
	}
}

GameObject* SceneLoader::LoadGameObject(const std::string& sceneName, XMLNode* gameObjectNode)
{
	if (gameObjectNode == NULL)
		return NULL;

	GameObject* gameObject = new GameObject(gameObjectNode->GetAttribAsString("name"));

	LayerId layerId = (LayerId)(1 << gameObjectNode->GetAttribAsInt32("layer", 0));
	gameObject->SetLayerId(layerId);

	for (uint32_t i = 0; i < gameObjectNode->GetChildrenCount(); i++)
	{
		XMLNode* node = gameObjectNode->GetChild(i);
		if (node == NULL)
			continue;

		if (node->GetName() == "Transform")
		{
			sm::Vec3 position = DemoUtils::ParseVector3(node->GetAttribAsString("position", "0,0,0"), ",");
			sm::Vec4 rotation = DemoUtils::ParseVector4(node->GetAttribAsString("rotation", "0,1,0,0"), ",");
			sm::Vec3 scale = DemoUtils::ParseVector3(node->GetAttribAsString("scale", "1,1,1"), ",");

			gameObject->Transform.SetLocalPosition(position);
			gameObject->Transform.SetLocalRotation(sm::Quat::FromAngleAxis(rotation.x, sm::Vec3(rotation.y, rotation.z, rotation.w))); // x as angle, rest as axis
			gameObject->Transform.SetLocalScale(scale);
		}
		else if (node->GetName() == "Model")
		{
			std::string modelName = node->GetAttribAsString("name");
			std::string materialName = node->GetAttribAsString("material");

			Model* model = Content::Instance->Get<Model>(modelName);
			assert(model != NULL);

			Material* material = FindMaterial(materialName);
			if (material == NULL)
				material = FindMaterial("ErrorMaterial");

			for (uint32_t i = 0; i < model->GetMeshes().size(); i++)
			{
				Renderable* renderable = new Renderable(gameObject, model->GetMeshes()[i]->GetMesh(), material, 0, layerId);
				gameObject->AddRenderable(renderable);
			}
		}
		else if (node->GetName() == "Mesh")
		{
			std::string meshName = node->GetAttribAsString("name");
			std::string materialName = node->GetAttribAsString("material");

			Model* model = Content::Instance->Get<Model>(sceneName);
			assert(model != NULL);

			do
			{
				Mesh* mesh = model->FindMesh(meshName);
				if (mesh == NULL)
				{
					//assert(mesh != NULL);
					break;
				}

				Material* material = FindMaterial(materialName);
				if (material == NULL)
					material = FindMaterial("ErrorMaterial");

				Renderable* renderable = new Renderable(gameObject, mesh, material, 0, layerId);
				gameObject->AddRenderable(renderable);
			} while (false);
		}
		else if (node->GetName() == "Light")
		{
			Light* light = new Light(gameObject);
			gameObject->SetLight(light);
		}
		else if (node->GetName() == "Camera")
		{
			Camera* camera = new Camera(gameObject);
			camera->SetFov(node->GetAttribAsFloat("fov", Camera::DefaultFov));
			camera->SetNearPlane(node->GetAttribAsFloat("near_plane", Camera::DefaultNearPlane));
			camera->SetFarPlane(node->GetAttribAsFloat("far_plane", Camera::DefaultFarPlane));

			sm::Vec4 viewport = DemoUtils::ParseVector4(node->GetAttribAsString("viewport", "0,0,1,1"), ",");
			camera->SetViewport(viewport.x, viewport.y, viewport.z, viewport.w);

			sm::Vec4 clearColor = DemoUtils::ParseVector4(node->GetAttribAsString("clear_color", StringUtils::ToString(Camera::DefaultClearColor)), ",");
			camera->SetClearColor(clearColor);

			std::string clearFlag = node->GetAttribAsString("clear_flag", "color_and_depth");
			if (clearFlag == "color_and_depth")
				camera->SetClearFlag(Camera::ClearFlag_ColorAndDepth);
			else if (clearFlag == "color")
				camera->SetClearFlag(Camera::ClearFlag_Color);
			else if (clearFlag == "depth")
				camera->SetClearFlag(Camera::ClearFlag_Depth);
			else
			{
				assert(false);
			}

			std::string projection = node->GetAttribAsString("projection", "perspective");
			if (projection == "perspective")
				camera->SetProjectionType(Camera::ProjectionType_Perspective);
			else if (projection == "orthographics")
				camera->SetProjectionType(Camera::ProjectionType_Orthographics);
			else
			{
				assert(false);
			}

			camera->SetDepth(node->GetAttribAsInt32("depth"));

			Layers cullLayers = LayerId_All;
			std::string cullLayersStr = node->GetAttribAsString("cull_layers", "all");
			if (cullLayersStr != "all")
			{
				Layers cullLayers = 0;
				std::vector<int> layersNumbers;
				DemoUtils::ParseIntVector(cullLayersStr, layersNumbers, ",");
				for (uint32_t layersNumbersIndex = 0; layersNumbersIndex < layersNumbers.size(); layersNumbersIndex++)
					cullLayers |= (LayerId)1 << layersNumbers[layersNumbersIndex];
				camera->SetCullLayers(cullLayers);
			}

			gameObject->SetCamera(camera);
		}
		else if (node->GetName() == "Behaviour")
		{
			std::string behaviourName = node->GetAttribAsString("name");

			std::vector<Parameter> parameters;
			LoadParameters(node, parameters);

			Behaviour* behaviour = gameObject->AddBehaviour(behaviourName);
			if (behaviour != NULL)
			{
				for (uint32_t i = 0; i < parameters.size(); i++)
				{
					if (parameters[i].GetType() == Parameter::Type_Float)
						behaviour->SetParameter(parameters[i].GetName(), parameters[i].GetFloat());
					if (parameters[i].GetType() == Parameter::Type_Int)
						behaviour->SetParameter(parameters[i].GetName(), parameters[i].GetInt());
					else if (parameters[i].GetType() == Parameter::Type_Vec3)
						behaviour->SetParameter(parameters[i].GetName(), parameters[i].GetVec3());
					else if (parameters[i].GetType() == Parameter::Type_Vec4)
						behaviour->SetParameter(parameters[i].GetName(), parameters[i].GetVec4());
					else if (parameters[i].GetType() == Parameter::Type_String)
						behaviour->SetParameter(parameters[i].GetName(), parameters[i].GetString());
				}
			}
		}
	}

	return gameObject;
}

void SceneLoader::LoadParameters(XMLNode* parentNode, std::vector<Parameter>& parameters)
{
	if (parentNode == NULL)
		return;

	XMLNode* parametersNode = parentNode->GetChild("Parameters");
	if (parametersNode == NULL)
		return;

	for (uint32_t i = 0; i < parametersNode->GetChildrenCount(); i++)
	{
		Parameter parameter = LoadParameter(parametersNode->GetChild(i));
		parameters.push_back(parameter);
	}
}

Parameter SceneLoader::LoadParameter(XMLNode* parameterNode)
{
	assert(parameterNode != NULL);
	assert(parameterNode->GetName() == "Parameter");
	
	std::string name = parameterNode->GetAttribAsString("name");
	std::string typeString = parameterNode->GetAttribAsString("type");
	std::string valueString = parameterNode->GetAttribAsString("value");

	Parameter parameter(name);

	if (typeString == "float")
	{
		float value = StringUtils::ParseFloat(valueString);
		parameter.SetFloat(value);
	}
	else if (typeString == "int")
	{
		int value = StringUtils::ParseInt(valueString);
		parameter.SetInt(value);
	}
	else if (typeString == "vec3")
	{
		sm::Vec3 value = DemoUtils::ParseVector3(valueString, ",");
		parameter.SetVec3(value);
	}
	else if (typeString == "vec4")
	{
		sm::Vec4 value = DemoUtils::ParseVector4(valueString, ",");
		parameter.SetVec4(value);
	}
	else if (typeString == "string")
	{
		parameter.SetString(valueString);
	}
	else if (typeString == "texture")
	{
		Texture* texture = Content::Instance->Get<Texture>(valueString);
		if (texture != NULL)
			parameter.SetTexture(texture);
	}

	return parameter;
}

bool SceneLoader::LoadAdditive(const std::string& filename)
{
	Path scenePath(filename);

	std::string sceneName = scenePath.GetFilename();

	std::vector<XMLNode*> includeNodes;

	XMLNode* rootNode = XMLLoader::LoadFromFile(filename);

	for (uint32_t rootIndex = 0; rootIndex < rootNode->GetChildrenCount(); rootIndex++)
	{
		XMLNode* node = rootNode->GetChild(rootIndex);
		if (node == NULL)
			continue;

		if (node->GetName() == "IncludeScene")
		{
			includeNodes.push_back(node);
		}
		else if (node->GetName() == "Materials")
		{
			for (uint32_t materialIndex = 0; materialIndex < node->GetChildrenCount(); materialIndex++)
			{
				XMLNode* materialNode = node->GetChild(materialIndex);
				if (materialNode != NULL)
					m_materialNodes.push_back(Object(materialNode, sceneName));
			}
		}
		else if (node->GetName() == "GameObjects")
		{
			for (uint32_t gameObjectIndex = 0; gameObjectIndex < node->GetChildrenCount(); gameObjectIndex++)
			{
				XMLNode* gameObjectNode = node->GetChild(gameObjectIndex);
				if (gameObjectNode != NULL)
					m_gameObjectNodes.push_back(Object(gameObjectNode, sceneName));
			}
		}
		else if (node->GetName() == "Hierarchy")
		{
			LoadHierarchy(node);
		}
	}

	// Ladowanie scen z includow
	for (uint32_t includesIndex = 0; includesIndex < includeNodes.size(); includesIndex++)
	{
		std::string includeSceneFilename =
			scenePath.GetPath() + includeNodes[includesIndex]->GetAttribAsString("name") + ".scene";
		
		LoadAdditive(includeSceneFilename);
	}

	return true;
}

void SceneLoader::BuildScene(BaseScene* scene)
{
	for (uint32_t i = 0; i < m_materialNodes.size(); i++)
	{
		Material* material = LoadMaterial(m_materialNodes[i].XMLNode);
		if (material != NULL)
		{
			m_materials[material->GetName()] = material;
			Content::Instance->Add(material->GetName(), material);
		}
	}

	for (uint32_t i = 0; i < m_gameObjectNodes.size(); i++)
	{
		GameObject* gameObject = LoadGameObject(m_gameObjectNodes[i].SceneName, m_gameObjectNodes[i].XMLNode);
		//if (gameObject != NULL)
//			scene->m_gameObjects.push_back(gameObject);
	}

	for (uint32_t i = 0; i < m_hierarchyRootNodes.size(); i++)
	{
		SetGameObjectTransformHierarchy(m_hierarchyRootNodes[i], NULL);
	}
}

void SceneLoader::SetGameObjectTransformHierarchy(SceneLoader::Node* node, Transform* parent)
{
	assert(node != NULL);

	BaseScene* scene = ScenesManager::GetInstance()->GetActiveScene();

	GameObject* gameObject = scene->FindGameObject(node->Name);
	if (gameObject == NULL)
		return;

	gameObject->Transform.SetParent(parent);

	for (uint32_t i = 0; i < node->Children.size(); i++)
		SetGameObjectTransformHierarchy(node->Children[i], &gameObject->Transform);
}

void SceneLoader::LoadHierarchy(XMLNode* hierarchyNode)
{
	if (hierarchyNode == NULL)
		return;

	for (uint32_t i = 0; i < hierarchyNode->GetChildrenCount(); i++)
	{
		SceneLoader::Node* hNode = LoadHierarchyNode(hierarchyNode->GetChild(i));
		if (hNode != NULL)
			m_hierarchyRootNodes.push_back(hNode);
	}
}

SceneLoader::Node* SceneLoader::LoadHierarchyNode(XMLNode* node)
{
	if (node == NULL || node->GetName() != "Node")
		return NULL;

	SceneLoader::Node* hNode = new SceneLoader::Node(node->GetAttribAsString("name"));

	for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
	{
		SceneLoader::Node* hChildNode = LoadHierarchyNode(node->GetChild(i));
		if (hChildNode != NULL)
		{
			hChildNode->Parent = hNode;
			hNode->Children.push_back(hChildNode);
		}
	}

	return hNode;
}


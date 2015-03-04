#include "Material.h"
#include "Shader.h"
#include "BuiltInShaderParams.h"

Material::Material() :
	m_builtInShaderParams(0)
{	
	diffuseColor.Set(0.6f, 0.6f, 0.6f, 1.0f);
	specularColor.Set(1.0f, 1.0f, 1.0f);

	glossiness = 0.3f;
	specularLevel = 1.0f;
	reflectionValue = 0.0f;

	diffuseTex = NULL;
	opacityTex = NULL;
	normalTex = NULL;
	lightmapTex = NULL;
	//environmentTex = NULL;
}

Material::~Material(void)
{
}

float& Material::Opacity()
{
	return diffuseColor.w;
}

bool Material::IsOpacity() const
{
	return diffuseColor.w < 1.0f;
}

void Material::SetShader(Shader* shader)
{
	m_shader = shader;

	m_builtInShaderParams = BuiltInShaderParams::GetShaderParams(m_shader);
}

void Material::SetParameter(const std::string& name, float value)
{
	m_parameters[name].SetFloat(value);
}

void Material::SetParameter(const std::string& name, const sm::Vec3& value)
{
	m_parameters[name].SetVec3(value);
}

void Material::SetParameter(const std::string& name, const sm::Vec4& value)
{
	m_parameters[name].SetVec4(value);
}

void Material::SetupMaterial()
{
	SetupRenderState();
	SetupShader();
}

void Material::SetupShader()
{
	m_shader->UseProgram();

	BuiltInShaderParams::SetShaderBuiltInParams(m_shader, m_builtInShaderParams);

	ParametersMap::iterator it;

	for (it = m_parameters.begin(); it != m_parameters.end(); ++it)
	{
		Parameter& parameter = it->second;

		switch (parameter.GetType())
		{
		case Parameter::Type_Float:
			m_shader->SetParameter(it->first.c_str(), parameter.GetFloat());
			break;

		case Parameter::Type_Vec3:
			m_shader->SetParameter(it->first.c_str(), parameter.GetVec3());
			break;

		case Parameter::Type_Vec4:
			m_shader->SetParameter(it->first.c_str(), parameter.GetVec4());
			break;
		}
	}
}

const std::string& Material::GetName() const
{
	return name;
}
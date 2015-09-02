#include "Material.h"
#include "Shader.h"
#include "BuiltInShaderParams.h"

Material::Material() :
	m_builtInShaderParams(0),
	m_isOpacity(false)
{
}

Material::~Material(void)
{
}

void Material::SetOpacity(bool opacity)
{
	m_isOpacity = opacity;
}

bool Material::IsOpacity() const
{
	return m_isOpacity;
}

void Material::SetShader(Shader* shader)
{
	m_shader = shader;

	m_builtInShaderParams = BuiltInShaderParams::GetShaderParams(m_shader);
}

Shader* Material::GetShader() const
{
	return m_shader;
}

void Material::SetParameter(const std::string& name, float value)
{
	m_parameters[name].SetFloat(value);
}

sm::Vec3 Material::GetParameterVec3(const std::string& name)
{
	return m_parameters[name].GetVec3();
}

sm::Vec4 Material::GetParameterVec4(const std::string& name)
{
	return m_parameters[name].GetVec4();
}

BaseTexture* Material::GetParameterTexture(const std::string& name)
{
	return m_parameters[name].GetTexture();
}

float Material::GetParameterFloat(const std::string& name)
{
	return m_parameters[name].GetFloat();
}

void Material::SetParameter(const std::string& name, const sm::Vec2& value)
{
	m_parameters[name].SetVec2(value);
}

void Material::SetParameter(const std::string& name, const sm::Vec3& value)
{
	m_parameters[name].SetVec3(value);
}

void Material::SetParameter(const std::string& name, const sm::Vec4& value)
{
	m_parameters[name].SetVec4(value);
}

void Material::SetParameter(const std::string& name, BaseTexture* value)
{
	m_parameters[name].SetTexture(value);
}

void Material::SetupMaterial()
{
	SetupRenderState();
	SetupShader();
}

void Material::SetupShader()
{
	if (IsOpacity())
	{
		glEnable(GL_BLEND);
		glDepthMask(false);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDepthMask(true);
		glDisable(GL_BLEND);
	}

	m_shader->UseProgram();

	BuiltInShaderParams::SetShaderBuiltInParams(m_shader, m_builtInShaderParams);

	ParametersMap::iterator it;

	int textureChannel = 0;

	for (it = m_parameters.begin(); it != m_parameters.end(); ++it)
	{
		Parameter& parameter = it->second;

		switch (parameter.GetType())
		{
		case PropertyType_Float:
			m_shader->SetParameter(it->first.c_str(), parameter.GetFloat());
			break;

		case PropertyType_Vec3:
			m_shader->SetParameter(it->first.c_str(), parameter.GetVec3());
			break;

		case PropertyType_Vec4:
			m_shader->SetParameter(it->first.c_str(), parameter.GetVec4());
			break;

		case PropertyType_Texture:
			m_shader->SetTextureParameter(it->first.c_str(), textureChannel, parameter.GetTexture()->GetId());
			textureChannel++;
			break;
		}
	}
}

const std::string& Material::GetName() const
{
	return name;
}


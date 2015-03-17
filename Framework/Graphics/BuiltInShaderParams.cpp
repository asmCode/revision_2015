#include "BuiltInShaderParams.h"
#include "Shader.h"

const std::string* InitParamsNames()
{
	return NULL;
}

const std::string* BuiltInShaderParams::ParamsNames = InitParamsNames();

sm::Matrix BuiltInShaderParams::m_paramWorld;
sm::Matrix BuiltInShaderParams::m_paramView;
sm::Matrix BuiltInShaderParams::m_paramProj;
sm::Matrix BuiltInShaderParams::m_paramViewProj;
sm::Matrix BuiltInShaderParams::m_paramWorldViewProj;
sm::Vec3 BuiltInShaderParams::m_paramPointLightPosition;
sm::Vec3 BuiltInShaderParams::m_paramEyePosition;

BuiltInShaderParams::Params BuiltInShaderParams::GetShaderParams(Shader* shader)
{
	BuiltInShaderParams::Params params = 0;

	if (shader->HasUniform("u_builtin_world"))
		params |= BuiltInShaderParams::ParamFlag_World;
	if (shader->HasUniform("u_builtin_view"))
		params |= BuiltInShaderParams::ParamFlag_View;
	if (shader->HasUniform("u_builtin_proj"))
		params |= BuiltInShaderParams::ParamFlag_Proj;
	if (shader->HasUniform("u_builtin_viewProj"))
		params |= BuiltInShaderParams::ParamFlag_ViewProj;
	if (shader->HasUniform("u_builtin_worldViewProj"))
		params |= BuiltInShaderParams::ParamFlag_WorldViewProj;
	if (shader->HasUniform("u_builtin_pointLightPosition"))
		params |= BuiltInShaderParams::ParamFlag_PointLightPosition;
	if (shader->HasUniform("u_builtin_eyePosition"))
		params |= BuiltInShaderParams::ParamFlag_EyePosition;

	return params;
}

void BuiltInShaderParams::SetShaderBuiltInParams(Shader* shader, Params params)
{
	if ((params & BuiltInShaderParams::ParamFlag_World) == BuiltInShaderParams::ParamFlag_World)
		shader->SetMatrixParameter("u_builtin_world", m_paramWorld);

	if ((params & BuiltInShaderParams::ParamFlag_View) == BuiltInShaderParams::ParamFlag_View)
		shader->SetMatrixParameter("u_builtin_view", m_paramView);

	if ((params & BuiltInShaderParams::ParamFlag_Proj) == BuiltInShaderParams::ParamFlag_Proj)
		shader->SetMatrixParameter("u_builtin_proj", m_paramProj);

	if ((params & BuiltInShaderParams::ParamFlag_ViewProj) == BuiltInShaderParams::ParamFlag_ViewProj)
		shader->SetMatrixParameter("u_builtin_viewProj", m_paramViewProj);

	if ((params & BuiltInShaderParams::ParamFlag_WorldViewProj) == BuiltInShaderParams::ParamFlag_WorldViewProj)
		shader->SetMatrixParameter("u_builtin_worldViewProj", m_paramWorldViewProj);

	if ((params & BuiltInShaderParams::ParamFlag_PointLightPosition) == BuiltInShaderParams::ParamFlag_PointLightPosition)
		shader->SetParameter("u_builtin_pointLightPosition", m_paramPointLightPosition);

	if ((params & BuiltInShaderParams::ParamFlag_EyePosition) == BuiltInShaderParams::ParamFlag_EyePosition)
		shader->SetParameter("u_builtin_eyePosition", m_paramEyePosition);
}

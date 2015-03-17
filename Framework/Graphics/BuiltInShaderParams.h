#pragma once

#include <../Math/Matrix.h>
#include <string>

class Shader;

class BuiltInShaderParams
{
public:
	typedef unsigned Params;

	enum ParamFlag
	{
		ParamFlag_World = 1 << 0,
		ParamFlag_View = 1 << 1,
		ParamFlag_Proj = 1 << 2,
		ParamFlag_ViewProj = 1 << 3,
		ParamFlag_WorldViewProj = 1 << 4,
		ParamFlag_PointLightPosition = 1 << 5,
		ParamFlag_EyePosition = 1 << 6
	};

	static const std::string* ParamsNames;

	static sm::Matrix m_paramWorld;
	static sm::Matrix m_paramView;
	static sm::Matrix m_paramProj;
	static sm::Matrix m_paramViewProj;
	static sm::Matrix m_paramWorldViewProj;
	static sm::Vec3 m_paramPointLightPosition;
	static sm::Vec3 m_paramEyePosition;

	static Params GetShaderParams(Shader* shader);
	static void SetShaderBuiltInParams(Shader* shader, Params params);
};

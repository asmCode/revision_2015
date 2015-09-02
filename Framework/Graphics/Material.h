#ifndef MATERIAL
#define MATERIAL

#include <Math\Vec2.h>
#include <Math\Vec3.h>
#include <Math\Vec4.h>
#include <string>
#include <map>
#include <stdint.h>

#include "Texture.h"
#include "DepthTexture.h"
#include "BuiltInShaderParams.h"
#include "../../Parameter.h"
//#include "CubeTexture.h"

class Shader;

class Material
{
private:
	typedef std::map<std::string, Parameter> ParametersMap;

public:
	std::string name;

	const std::string& GetName() const;

	Material(void);
	~Material(void);

	void SetupMaterial();

	void SetOpacity(bool opacity);
	virtual bool IsOpacity() const;

	void SetShader(Shader* shader);
	Shader* GetShader() const;
	sm::Vec3 GetParameterVec3(const std::string& name);
	sm::Vec4 GetParameterVec4(const std::string& name);
	BaseTexture* GetParameterTexture(const std::string& name);
	float GetParameterFloat(const std::string& name);
	void SetParameter(const std::string& name, float value);
	void SetParameter(const std::string& name, const sm::Vec2& value);
	void SetParameter(const std::string& name, const sm::Vec3& value);
	void SetParameter(const std::string& name, const sm::Vec4& value);
	void SetParameter(const std::string& name, BaseTexture* value);

	bool HasBuiltInShaderParam(BuiltInShaderParams::ParamFlag paramFlag);

protected:
	Shader* m_shader;

	uint32_t m_builtInShaderParams;

	ParametersMap m_parameters;

	bool m_isOpacity;

	virtual void SetupRenderState() {};
	virtual void SetupShader();
};

#endif // MATERIAL


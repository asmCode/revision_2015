#ifndef MATERIAL
#define MATERIAL

#include <Math\Vec3.h>
#include <Math\Vec4.h>
#include <string>
#include <map>
#include <stdint.h>

#include "Texture.h"
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
	
	sm::Vec4 diffuseColor;
	sm::Vec3 specularColor;

	float glossiness;
	float specularLevel;
	float reflectionValue; // for evironment mapping

	std::string diffuseTexName;
	Texture *diffuseTex;

	std::string opacityTexName;
	Texture *opacityTex;

	std::string normalTexName;
	Texture *normalTex;

	std::string environmentTexName;
	//CubeTexture *environmentTex;

	std::string lightmapTexName;
	Texture *lightmapTex;

	Material(void);
	~Material(void);

	float& Opacity();

	void SetupMaterial();

	virtual bool IsOpacity() const;

	void SetShader(Shader* shader);
	void SetParameter(const std::string& name, float value);
	void SetParameter(const std::string& name, const sm::Vec3& value);
	void SetParameter(const std::string& name, const sm::Vec4& value);

	bool HasBuiltInShaderParam(BuiltInShaderParams::ParamFlag paramFlag);

protected:
	Shader* m_shader;

	uint32_t m_builtInShaderParams;

	ParametersMap m_parameters;

	virtual void SetupRenderState() {};
	virtual void SetupShader();
};

#endif // MATERIAL


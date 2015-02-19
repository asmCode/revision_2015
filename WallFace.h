#pragma once

#include <Math/Matrix.h>
#include <stdint.h>

class Texture;
class Shader;
class PlaneMesh;

class WallFace
{
public:
	WallFace();
	virtual ~WallFace();

	void Initialize(int resolution);

	void SetMvpMatrix(const sm::Matrix& mvp);
	void Update(float time, float deltaTime);
	void Draw(
		uint32_t texId,
		int32_t diffTexId,
		int32_t noiseTexId,
		const sm::Matrix& world,
		const sm::Matrix& viewProj,
		const sm::Vec3& lightPosition);

private:
	PlaneMesh* m_planeMesh;
	Shader* m_wallFaceShader;
	sm::Matrix m_mvp;

	void SetupGraphicsState();
};

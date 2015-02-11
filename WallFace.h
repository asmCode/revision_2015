#pragma once

#include <Math/Matrix.h>

class Texture;
class Shader;
class PlaneMesh;

class WallFace
{
public:
	WallFace();
	virtual ~WallFace();

	void Initialize();

	void SetMvpMatrix(const sm::Matrix& mvp);
	void Update(float time, float deltaTime);
	void Draw(Texture* depth, const sm::Matrix& mvp);

private:
	PlaneMesh* m_planeMesh;
	Shader* m_wallFaceShader;
	sm::Matrix m_mvp;

	void SetupGraphicsState();
};

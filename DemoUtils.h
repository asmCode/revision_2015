#pragma once

#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>
#include <vector>

class Camera;

class DemoUtils
{
public:
	static sm::Vec3 GetRandomVector();
	static float GetPathLength(std::vector<sm::Vec3>& path);
	static sm::Matrix GetTriangleTransform(sm::Vec3* triangle);
	static std::string ToText(const sm::Vec3& value, const std::string& separator = ";");
	static std::string ToText(const sm::Vec4& value, const std::string& separator = ";");
	static std::string ToText(const sm::Quat& value, const std::string& separator = ";");
	static sm::Vec3 ParseVector3(const std::string& vectorStr, const std::string& separator = ";");
	static sm::Vec4 ParseVector4(const std::string& vectorStr, const std::string& separator = ";");
	static sm::Quat ParseQuat(const std::string& vectorStr, const std::string& separator = ";");
	static void SaveCamera(Camera* camera, int slot);
	static void LoadCamera(Camera* camera, int slot);
};

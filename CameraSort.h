#pragma once

class Camera;

class CameraSort
{
public:
	bool operator() (const Camera* camera1, const Camera* camera2);
};

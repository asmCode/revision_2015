#include "CameraSort.h"
#include "Camera.h"

bool CameraSort::operator() (const Camera* camera1, const Camera* camera2)
{
	return camera1->GetDepth() < camera2->GetDepth();
}

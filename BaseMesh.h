#pragma once

class BaseMesh
{
public:
	BaseMesh() {};
	virtual ~BaseMesh() {}

	virtual void Setup() {}
	virtual void Draw() = 0;
	virtual void Clean() {}
};

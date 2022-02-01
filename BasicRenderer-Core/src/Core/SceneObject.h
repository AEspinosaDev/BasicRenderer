#pragma once
#include <string>

class SceneObject
{
protected:
	std::string m_Name;
	float* location;
	float scale;

public:
	SceneObject(const std::string na) : m_Name(na), location(new float[3]), scale(1) { location[0] = 0; location[1] = 0; location[2] = 0; }

	SceneObject() : m_Name(""), location(new float[3]), scale(1) { location[0] = 0; location[1] = 0; location[2] = 0; }

	virtual void draw() = 0;

	virtual void setPosition(const float x, const float y, const float z) = 0;

	virtual float* getPosition() = 0;

	virtual void setScale(const float  s) = 0;

	virtual inline float getScale() { return scale; }
};


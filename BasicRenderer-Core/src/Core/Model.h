#pragma once
#include "Mesh.h"
#include "SceneObject.h"


class Model : public SceneObject {
private:

	Mesh* m_Mesh;
	Material* m_Mat;

public:

	Model(const std::string na, Mesh* me) :SceneObject(na), m_Mesh(me), m_Mat(nullptr) {}

	Model(const std::string na, Mesh* me, Material* ma) : SceneObject(na), m_Mesh(me), m_Mat(ma) {}

	Model() :SceneObject(), m_Mesh(nullptr), m_Mat(nullptr) {}

	~Model() {}

	void loadMesh(const std::string& pname);

	void setPosition(const float x, const float y, const float z);

	float* getPosition();

	void setScale(const float  s);

	void setRotation(const float angle, const int x, const int y, const int z);

	void loadMaterial(Material* m);

	inline Material* getMaterialReference() { return m_Mat; }

	void draw();

};
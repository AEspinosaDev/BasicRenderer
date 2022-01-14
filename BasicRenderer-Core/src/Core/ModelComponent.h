#pragma once
#include "Mesh.h"


class ModelComponent {
private:

	std::string m_Name;
	Mesh* m_Mesh;
	Material* m_Mat;
	float* location;
	float scale;
	


public:

	ModelComponent(const std::string na, Mesh* me) : m_Name(na),m_Mesh(me), m_Mat(nullptr), location(new float[3]), scale(1) {
		location[0] = 0; location[1] = 0; location[2] = 0;
	}
	ModelComponent(const std::string na, Mesh* me, Material* ma) : m_Name(na), m_Mesh(me), m_Mat(ma), location(new float[3]), scale(1) {
		location[0] = 0; location[1] = 0; location[2] = 0;
	}
	ModelComponent() :m_Mesh(nullptr), m_Name("scene_model_x"), m_Mat(nullptr), location(new float[3]), scale(1) {
		location[0] = 0; location[1] = 0; location[2] = 0;
	}
	~ModelComponent(){}

	void loadMesh(const std::string& pname) {
		if (m_Mesh != nullptr)
			delete m_Mesh;
		m_Mesh = new Mesh();
		m_Mesh->importFile(pname);
		m_Mesh->setSize(scale);
		m_Mesh->setPos(glm::vec3(location[0], location[1], location[2]));
	}
	void setPosition(const float x,const float y,const float z) {
		if (m_Mesh != nullptr) {
			location[0] = x; location[1] = y; location[2] = z;
			m_Mesh->setPos(glm::vec3(x, y, z));
		}
	}
	float* getPosition() {
		if (m_Mesh != nullptr) 
		std::cout << m_Name << " position is " << location[0] << ", " << location[1] << ", " << location[2] << "." << std::endl;
		return location;

	}
	void setScale(const float  s) {

		if (m_Mesh != nullptr) {
			scale = s;
			m_Mesh->setSize(s);
		}


	}
	float getScale() { return scale; }

	void setRotation(const float angle,const int x,const int y, const int z) {

		if (m_Mesh != nullptr) 
		m_Mesh->setRotation(angle, glm::vec3(x, y, z));
	}
	void loadMaterial(Material* m) {
		if (m_Mat != nullptr)
			delete m_Mat;
		m_Mat = m;
		if(m_Mesh!= nullptr)
			m_Mesh->setMaterial(m);
		else
			std::cout << "Model doesnt have any mesh loaded" << std::endl;
	}

	Material* getMaterialReference() { return m_Mat; }

	void draw() {

		if (m_Mesh != nullptr && m_Mat != nullptr)
			m_Mesh->draw();
		else
			std::cout << "Model doesnt have any mesh loaded" << std::endl;
	}

};
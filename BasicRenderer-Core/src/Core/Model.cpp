#include "Model.h"

void Model::loadMesh(const std::string& pname) {
	if (m_Mesh != nullptr)
		delete m_Mesh;
	m_Mesh = new Mesh();
	m_Mesh->importFile(pname);
	m_Mesh->setSize(scale);
	m_Mesh->setPos(glm::vec3(location[0], location[1], location[2]));
}

void Model::setPosition(const float x, const float y, const float z) {
	if (m_Mesh != nullptr) {
		location[0] = x; location[1] = y; location[2] = z;
		m_Mesh->setPos(glm::vec3(x, y, z));
	}
}
float* Model::getPosition() {
	if (m_Mesh != nullptr)
		std::cout << m_Name << " position is " << location[0] << ", " << location[1] << ", " << location[2] << "." << std::endl;
	return location;

}
void Model::setScale(const float  s) {

	if (m_Mesh != nullptr) {
		scale = s;
		m_Mesh->setSize(s);
	}


}

void Model::setRotation(const float angle, const int x, const int y, const int z) {

	if (m_Mesh != nullptr)
		m_Mesh->setRotation(angle, glm::vec3(x, y, z));
}

void Model::loadMaterial(Material* m) {
	if (m_Mat != nullptr)
		delete m_Mat;
	m_Mat = m;
	if (m_Mesh != nullptr)
		m_Mesh->setMaterial(m);
	else
		std::cout << "Model doesnt have any mesh loaded" << std::endl;
}

void Model::draw() {

	if (m_Mesh != nullptr && m_Mat != nullptr)
		m_Mesh->draw();
	else
		std::cout << "Model doesnt have any mesh loaded" << std::endl;
}

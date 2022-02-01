#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h> 
#include <VAO.h>
#include <Material.h>


class Mesh
{
	VAO m_Vao;
	//IBO m_Index;
	unsigned int m_IndexBufferID;
	unsigned int m_Triangles;
	glm::mat4	 m_Model;
	Material*    m_Mat;

public:
	Mesh() :m_IndexBufferID(-1), m_Triangles(-1), m_Model(glm::mat4(1.0f)), m_Mat(nullptr) {}

	~Mesh() {}
	
	inline glm::mat4 getModel() const { return m_Model; }
	
	inline void setPos(glm::vec3 p){this->m_Model = glm::translate(glm::mat4(1.0f), p);}
	
	inline void setOffset(glm::vec3 p){this->m_Model = glm::translate(m_Model, p);}
	
	inline void setSize(float n) { m_Model = glm::scale(m_Model, glm::vec3(n, n, n)); }
	
	inline void setRotation(float angle, glm::vec3 axis){ m_Model = glm::rotate(m_Model, glm::radians(angle), axis); }
	
	inline void setModel(glm::mat4 m) {	m_Model = m;}



	void init(unsigned int nTris, unsigned int nVertex, const unsigned int* triangleId, const float* vertexPos,
		const float* vertexColor, const float* vertexNormal,
		const float* vertexTexCoord, const float* vertexTangent);

	inline void setMaterial(Material* material) {
		m_Mat = material;
	}

	inline Material* getMaterial() {
		return m_Mat;
	}

	
	void draw();

	void importFile(const std::string& pname);

};



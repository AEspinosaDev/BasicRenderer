#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h> 
//#include "Material.h"
#include <VAO.h>
#include <IBO.h>
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
		const float* vertexTexCoord, const float* vertexTangent) {

		
		m_Triangles = nTris * 3;
		m_Vao.bind();

		if (vertexPos != NULL) {
			VBO pos_b(vertexPos, nVertex * sizeof(float) * 3);
			VBLayout layout0;
			layout0.push<float>(3);
			m_Vao.addBuffer(pos_b, layout0);
		}

		
		if (vertexNormal != NULL) {
			VBO normal_b(vertexNormal, nVertex * sizeof(float) * 3);
			VBLayout layout2;
			layout2.push<float>(3);
			m_Vao.addBuffer(normal_b, layout2);
		}

		if (vertexTexCoord != NULL) {
			VBO texCoord_b(vertexTexCoord, nVertex * sizeof(float) * 2);
			VBLayout layout3;
			layout3.push<float>(2);
			m_Vao.addBuffer(texCoord_b, layout3);
		}

		if (vertexTangent != NULL) {
			VBO tangent_b(vertexTangent, nVertex * sizeof(float) * 3);
			VBLayout layout4;
			layout4.push<float>(3);
			m_Vao.addBuffer(tangent_b, layout4);
		}
		if (vertexColor != NULL) {
			VBO color_b(vertexColor, nVertex * sizeof(float) * 3);
			VBLayout layout1;
			layout1.push<float>(3);
			m_Vao.addBuffer(color_b, layout1);
		}
		
		IBO trisIndex(triangleId, m_Triangles);
		
		
	}
	inline void setMaterial(Material* material) {
		m_Mat = material;
	}
	inline Material* getMaterial() {
		return m_Mat;
	}

	
	void draw() {
		
		m_Mat->getShader()->bind();
		m_Mat->getShader()->setMat4("model", m_Model);
		m_Vao.bind();

		m_Mat->draw();

		GLcall(glDrawElements(GL_TRIANGLES, m_Triangles, GL_UNSIGNED_INT, (void*)0));
		m_Mat->getShader()->unbind();

	}

	void importFile(const std::string& pname) {
		
		const std::string pFile = modelPath + pname;
		Assimp::Importer importer;

		const aiScene* sc;
		sc = importer.ReadFile(pFile,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (!sc) {

			std::cout << "Error al importar" << std::endl;
		}

		std::cout << "Se han cargado " << sc->mNumMeshes << " meshes" << std::endl;

		for (unsigned int n = 0; n < sc->mNumMeshes; ++n)
		{
			const aiMesh* mesh = sc->mMeshes[n];

			unsigned int* faceArray;
			faceArray = (unsigned int*)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
			unsigned int faceIndex = 0;

			float* vertexArray{};
			unsigned int vertexIndex = 0;
			float* normalArray{};
			unsigned int normalIndex = 0;

			float* textCoordArray{};

			unsigned int tangentsIndex = 0;
			float* tangentsArray{};



			if (mesh->HasFaces()) {
				for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
					const aiFace* face = &mesh->mFaces[t];
					memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
					faceIndex += 3;
				}
			}

			if (mesh->HasPositions()) {  //Idem: por defecto siempre tiene.

				vertexArray = (float*)malloc(sizeof(float) * mesh->mNumVertices * 3);


				for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
					const aiVector3D* vertex = &mesh->mVertices[k];
					memcpy(&vertexArray[vertexIndex], &(vertex->x), sizeof(float));
					memcpy(&vertexArray[vertexIndex + 1], &(vertex->y), sizeof(float));
					memcpy(&vertexArray[vertexIndex + 2], &(vertex->z), sizeof(float));
					vertexIndex += 3;
				}
			}
			if (mesh->HasNormals()) {
				normalArray = (float*)malloc(sizeof(float) * mesh->mNumVertices * 3);

				for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
					const aiVector3D* a_normal = &mesh->mNormals[k];
					memcpy(&normalArray[normalIndex], &(a_normal->x), sizeof(float));
					memcpy(&normalArray[normalIndex + 1], &(a_normal->y), sizeof(float));
					memcpy(&normalArray[normalIndex + 2], &(a_normal->z), sizeof(float));
					normalIndex += 3;
				}
			}
			if (mesh->mTextureCoords != NULL) {
				textCoordArray = (float*)malloc(sizeof(float) * 2 * mesh->mNumVertices);

				for (int k = 0; k < mesh->mNumVertices; k++) {
					const aiVector3D* a_textCoord = &mesh->mTextureCoords[0][k];

					memcpy(&textCoordArray[k * 2], &(a_textCoord->x), sizeof(float));
					memcpy(&textCoordArray[k * 2 + 1], &(a_textCoord->y), sizeof(float));

				}

			}
			if (mesh->HasTangentsAndBitangents()) {
				tangentsArray = (float*)malloc(sizeof(float) * mesh->mNumVertices * 3);
				for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
					const aiVector3D* a_tangent = &mesh->mTangents[k];
					memcpy(&tangentsArray[tangentsIndex], &(a_tangent->x), sizeof(float));
					memcpy(&tangentsArray[tangentsIndex + 1], &(a_tangent->y), sizeof(float));
					memcpy(&tangentsArray[tangentsIndex + 2], &(a_tangent->z), sizeof(float));
					normalIndex += 3;
				}
			}
			this->init(mesh->mNumFaces, mesh->mNumVertices,faceArray, vertexArray, 0, normalArray, textCoordArray, tangentsArray);


		}
	}
	

	
};



#pragma once
#include <Shader.h>
#include <Texture.h>

class Material {
private:

	Shader* m_shader;
	Texture* colorTex;
	Texture* normalTex;
	Texture* specularTex;
	Texture* roughnessTex;
	Texture* emiTex;

public:
	Material(Shader* shader, const std::string& colorPath, const std::string& normalPath, const std::string& specularPath, const std::string& roughnessPath, const std::string& emiPath): m_shader(shader) {
		
		m_shader->bind();
		colorTex = new Texture(colorPath);
		m_shader->setInt("colorTex", 0);
		normalTex = new Texture(normalPath);
		m_shader->setInt("normalTex", 1);
		specularTex = new Texture(specularPath);
		m_shader->setInt("specTex", 2);
		roughnessTex = new Texture(roughnessPath);
		m_shader->setInt("roughTex", 3);
		emiTex = new Texture(emiPath);
		m_shader->setInt("emiTex", 4);
		m_shader->unbind();

	}
	Material(Shader* shader): m_shader(shader) {

		colorTex = nullptr;
		normalTex = nullptr;
		specularTex = nullptr;
		roughnessTex = nullptr;
		emiTex = nullptr;

	}
	~Material(){}
	void draw() {
		
		m_shader->bind();
		if(colorTex != nullptr)
		colorTex->bind(0);
		if(normalTex != nullptr)
		normalTex->bind(1);
		if(specularTex != nullptr)
		specularTex->bind(2);
		if(roughnessTex != nullptr)
		roughnessTex->bind(3);
		if(emiTex != nullptr)
		emiTex->bind(4);

	}

	inline Shader* getShader() { return m_shader; }

	void addColorTex(Texture* t) {
		colorTex = t;
		m_shader->bind();
		m_shader->setInt("colorTex", 0);
		m_shader->unbind();
	}
	void addNormalTex(Texture* t) {
		normalTex = t;
		m_shader->bind();
		m_shader->setInt("normalTex", 1);
		m_shader->unbind();
	}
	void addSpecularTex(Texture* t) {
		specularTex = t;
		m_shader->bind();
		m_shader->setInt("specTex", 2);
		m_shader->unbind();
	}
	void addRoughnessTex(Texture* t) {
		roughnessTex = t;
		m_shader->bind();
		m_shader->setInt("roughTex", 3);
		m_shader->unbind();
	}

};


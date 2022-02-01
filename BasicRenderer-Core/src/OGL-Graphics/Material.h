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
	Material(Shader* shader, const std::string& colorPath, const std::string& normalPath, const std::string& specularPath, const std::string& roughnessPath, const std::string& emiPath);

	Material(Shader* shader);
	
	~Material(){}

	void draw();

	inline Shader* getShader() { return m_shader; }

	void addColorTex(Texture* t);

	void addNormalTex(Texture* t);

	void addSpecularTex(Texture* t);

	void addRoughnessTex(Texture* t);

};


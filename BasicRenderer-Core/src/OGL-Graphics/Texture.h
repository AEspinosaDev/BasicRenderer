#pragma once
#include "Renderer.h"
#include "FreeImage.h"


class Texture {

	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	unsigned int m_Width, m_Height;

public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot) const;
	void unbind() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }

private:
	unsigned char* loadTexture(const char* fileName, unsigned int& w, unsigned int& h);
	
};

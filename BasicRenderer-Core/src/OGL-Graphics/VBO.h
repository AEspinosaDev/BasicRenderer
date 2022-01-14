#pragma once
#include "Core.h"



//Vertex buffer object

class VBO {
private:
	unsigned int m_RendererID;
public:
	VBO(const void* data, unsigned int size) {

		GLcall(glGenBuffers(1, &m_RendererID));
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLcall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	~VBO() {
		//GLcall(glDeleteBuffers(1, &m_RendererID))
	}

	void bind() const {
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void unbind() const {
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}




};
#pragma once
#include "Core.h"


//Index buffer object

class IBO {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IBO(const unsigned int* data, unsigned int count): m_Count(count) {
		ASSERT(sizeof(GLuint) == sizeof(unsigned int));

		GLcall(glGenBuffers(1, &m_RendererID));
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GLcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	~IBO() {
		//GLcall(glDeleteBuffers(1, &m_RendererID))
	}

	void bind() const {
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void unbind() const {
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	inline unsigned int getCount() const { return m_Count; }
	inline unsigned int getID() const { return m_RendererID; }

};
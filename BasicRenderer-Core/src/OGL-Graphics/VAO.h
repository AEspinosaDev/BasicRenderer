#pragma once
#include "Core.h"
#include "VBO.h"
#include "VBLayout.h"


class VAO {
	unsigned int m_RendererID;
	unsigned int m_layoutCount;

public:
	VAO(): m_layoutCount(0) {
		GLcall(glGenVertexArrays(1, &m_RendererID));
		
	}

	~VAO() {
		GLcall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void addBuffer(const VBO& vbo, const VBLayout& layout) {
		bind();
		vbo.bind();
		unsigned int offset = 0;
		const auto& elements = layout.getElements();

		for (int i =0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLcall(glEnableVertexAttribArray(m_layoutCount));
		GLcall(glVertexAttribPointer(m_layoutCount, element.count, element.type,
			element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count*VBElement::getSizeOf(element.type);
		m_layoutCount++;
		}
	}
	
	void bind() const {

		GLcall(glBindVertexArray(m_RendererID));
	}
	void unbind() const {

		GLcall(glBindVertexArray(0));
	}
};

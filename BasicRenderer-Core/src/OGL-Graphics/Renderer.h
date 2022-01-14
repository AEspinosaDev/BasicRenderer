#pragma once
#include "VAO.h"
#include "IBO.h"
#include "Shader.h"


class RendererER {
public:
   

    void draw(const VAO& vao, const IBO& ibo, const Shader& shader) const {

        shader.bind();
        vao.bind();
        ibo.bind();

        GLcall(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));

    }

    void clear() const {
        GLcall(glClear(GL_COLOR_BUFFER_BIT));
    }














};

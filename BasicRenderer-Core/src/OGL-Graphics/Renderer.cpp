#include "Renderer.h"

void RendererER::draw(const VAO& vao, const IBO& ibo, const Shader& shader) const {

    shader.bind();
    vao.bind();
    ibo.bind();

    GLcall(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));

}

void RendererER::clear() const {
    GLcall(glClear(GL_COLOR_BUFFER_BIT));
}
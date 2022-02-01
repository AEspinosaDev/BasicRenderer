#pragma once
#include "VAO.h"
#include "IBO.h"
#include "Shader.h"


class RendererER {
public:
   

    void draw(const VAO& vao, const IBO& ibo, const Shader& shader) const;

    void clear() const;

};

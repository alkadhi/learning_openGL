#pragma once

#include "glad.h"
#include "VBO.hpp"

class VAO{
    public:
        GLuint ID;
        VAO();

        void linkVBO(VBO VBO, GLuint layout);

        void bind();
        void unbind();
        void free();
};

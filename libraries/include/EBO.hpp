#pragma once

#include "glad.h"

class EBO{
    public:
        GLuint ID;
        EBO(GLuint* indecies, GLsizeiptr size);

        void bind();
        void unbind();
        void free();
};

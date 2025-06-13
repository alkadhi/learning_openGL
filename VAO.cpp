#include "libraries/include/VAO.hpp"

VAO::VAO(){
    glGenVertexArrays(1, &ID);
}

void VAO::linkVBO(VBO VBO, GLuint layout){
    VBO.bind();

    //gives it info on how much space to take in memory
                                                    // there is three floats for each vertex!
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(layout);

    VBO.unbind();
}

void VAO::bind(){
    glBindVertexArray(ID);
}

void VAO::unbind(){
    glBindVertexArray(0);
}

void VAO::free(){
    glDeleteVertexArrays(1, &ID);
}

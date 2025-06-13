#include <cstddef>
#include <cstdio>
#include <iostream>
#include "libraries/include/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <math.h>
#include <GLFW/glfw3native.h>

#include "libraries/include/shader.hpp"
#include "libraries/include/VAO.hpp"
#include "libraries/include/VBO.hpp"
#include "libraries/include/EBO.hpp"

using namespace std;

int main(){

    const char* vertexSource("shaders/generic.vert");
    const char* fragmentSource("shaders/generic.frag");

    // initializes window
    glfwInit();

    //informs the windowing system GLFW the version as well as that we are using the CORE profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //sets up a triangle
    GLfloat triangle[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5 / 2, 0.5 * float(sqrt(3)) / 6, 0.0f,
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
    };

    GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1

    };


    //creating a GLFW window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "Learning OpenGL", NULL, NULL);

    //if the create-window function fails then we handle that
    if (window == NULL){
        std::cout << "Failed to open a GLFW window" << endl;
        return -1;
    }

    //introduces the window object to the current context
    glfwMakeContextCurrent(window);

    //loads glad into memory
    gladLoadGL();

    //sets the viewport to draw on
    glViewport(0, 0, 800, 600);

    Shader shader(vertexSource, fragmentSource);

    VAO vao;
    vao.bind();

    VBO vbo(triangle, sizeof(triangle));
    EBO ebo(indices, sizeof(indices));

    vao.linkVBO(vbo, 0);
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    //recommended to add
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // loads color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);    // the last number is the alpha channel which allows transparency
    //sets the mode
    glClear(GL_COLOR_BUFFER_BIT);

    //this informs the GPU to do the buffer switching on the window
    glfwSwapBuffers(window);

    //keeps window open until there is a reason it should close
    while(!glfwWindowShouldClose(window)){

        // loads color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);    // the last number is the alpha channel which allows transparency
        //sets the mode
        glClear(GL_COLOR_BUFFER_BIT);

        shader.activate();
        vao.bind();
        //sets the mode so that the GPU draws together by three
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //allows buffer swapping so that updates can be shown
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    vao.free();
    vbo.free();
    ebo.free();
    shader.free();

    //destorys window and all there is of the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

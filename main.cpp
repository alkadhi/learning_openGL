#include <iostream>
#include "libraries/include/glad.h"
#include <GLFW/glfw3.h>

using namespace std;

const char* vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\n\tgl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";


int main(){

    // initializes window
    glfwInit();

    //informs the windowing system GLFW the version as well as that we are using the CORE profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //creating a GLFW window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "Learning OpenGL", NULL, NULL);
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

    // loads color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    //sets the mode
    glClear(GL_COLOR_BUFFER_BIT);
    //acts
    glfwSwapBuffers(window);

    //keeps window open until there is a reason it should close
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    //destorys window and all there is of the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

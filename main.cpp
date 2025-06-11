#include <cstddef>
#include <cstdio>
#include <iostream>
#include "libraries/include/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <math.h>
#include <GLFW/glfw3native.h>

using namespace std;

int main(){

    //opens both the vertex shader and fragment shaders
    ifstream vertexShaderFile("shaders/generic.vert");
    ifstream fragmentShaderFile("shaders/generic.frag");

    /***
    *   The vertex shader collects the array of vertecies and performs operations on them
    *   The fragment shader applies color to the vertecies; the fragment shader occurs after the
    *   geometry shader which creates the shapes
    ***/

    //  this is where the code while be read into
    string temp = "";
    string vertexShaderSourceString = "";
    string fragmentShaderSourceString = "";

    if (vertexShaderFile.is_open() && fragmentShaderFile.is_open()){
        while(getline(vertexShaderFile, temp)){
            vertexShaderSourceString.append(temp + "\n");
        }
        temp = "";
        while (getline(fragmentShaderFile, temp)){
            fragmentShaderSourceString.append(temp + "\n");
        }
        temp = "";
    } else {
        cerr << "MISSING SHADERS" << endl;
    }

    const char* vertexShaderSource = vertexShaderSourceString.c_str();
    const char* fragmentShaderSource = fragmentShaderSourceString.c_str();

    //  closes the files
    vertexShaderFile.close();
    fragmentShaderFile.close();

    // initializes window
    glfwInit();

    //informs the windowing system GLFW the version as well as that we are using the CORE profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat triangle[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(vertexShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    //destorys window and all there is of the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

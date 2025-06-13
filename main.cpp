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

    //this is where the files are stored
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

    //sets up a triangle
    GLfloat triangle[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
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

    //creates a vertex and fragment shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //binds the combo
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //we have no use of the two as they have now been added to the shaderProgram
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // vertex array object and vertex buffer object; one holds the VBOs and the other holds the vertecies of the perimitive
    GLuint VAO, VBO;

    // this must be in order!!!
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    //gives it info on how much space to take in memory
                                                    // there is three floats for each vertex!
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //recommended to add
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
        //sets the mode so that the GPU draws together by three
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //allows buffer swapping so that updates can be shown
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

#pragma once

#include "glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

using namespace std;

string get_file_contents(const char* filename);

class Shader{

    public:
        GLuint ID;
        Shader(const char* vertexFile, const char* fragmentFile);

        void activate();
        void free();
};

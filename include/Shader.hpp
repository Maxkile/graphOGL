//
// Created by maxkile on 07.12.2019.
//

#pragma once

#include "base/stdafx.hpp"
#include "base/Constants.hpp"
#include <fstream>
#include <sstream>
#include <string>


class Shader
{
    GLchar* shaderSources;
    GLchar infoLog[INFOSIZE];

    GLuint customShaderID;
    GLint successfulCompile;

public:

    explicit Shader();

    void readSourceToString(const std::string& filename);

    GLint compile(GLint shaderType);

    void deleteShader();

    GLint isCompiled() const;

    GLchar* getInfoLog();

    GLuint getCustomShaderID() const;

    const GLchar* getSource() const;

    ~Shader();
};
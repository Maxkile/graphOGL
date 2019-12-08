//
// Created by maxkile on 07.12.2019.
//

#include "../include/Shader.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>

Shader::Shader()
{
    for(GLchar & c : infoLog)
    {
        c = '\0';
    }
    successfulCompile = false;
}

void Shader::readSourceToString(const std::string& filename)
{
    std::ifstream shaderSourceFile(filename,std::ifstream::in);
    if (shaderSourceFile.fail())
    {
        throw std::ios_base::failure("Error when opening file " + filename);
    }
    std::stringstream shaderSource;
    std::string line;
    while(getline(shaderSourceFile,line))
    {
        line.append("\n");
        shaderSource << line;
    }
    shaderSourceFile.close();

    this->shaderSources = new char[shaderSource.str().size()];
    strcpy(this->shaderSources,shaderSource.str().c_str());
}

GLint Shader::compile(GLint shaderType)
{
    if ((shaderType != GL_VERTEX_SHADER) && (shaderType != GL_FRAGMENT_SHADER))
    {
        std::cerr << "Wrong shader type!"  + std::to_string(shaderType) << std::endl;
        return GL_FALSE;
    }
    else
    {
        this->customShaderID = glCreateShader(shaderType);

        glShaderSource(this->customShaderID,1,&shaderSources, nullptr);//second is number of lines in shaders,third is string source code
        glCompileShader(this->customShaderID);
        glGetShaderiv(this->customShaderID, GL_COMPILE_STATUS, &successfulCompile);
        if(successfulCompile == GL_FALSE)
        {
            glGetShaderInfoLog(this->customShaderID, INFOSIZE, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        return successfulCompile;
    }
}

void Shader::deleteShader()
{
    glDeleteShader(customShaderID);
}

GLint Shader::isCompiled() const
{
    return successfulCompile;
}

GLchar* Shader::getInfoLog()
{
    return infoLog;
}

GLuint Shader::getCustomShaderID() const
{
    return customShaderID;
}

const GLchar* Shader::getSource() const
{
    return shaderSources;
}

Shader::~Shader()
{
    delete shaderSources;
}

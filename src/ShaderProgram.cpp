//
// Created by maxkile on 07.12.2019.
//

#include "../include/ShaderProgram.hpp"
#include <iostream>

ShaderProgram::ShaderProgram()
{
    for(GLchar& c:infoLog)
    {
        c = '\0';
    }
    successfulLink = false;
    successfulUse = false;
    shaderProgramID = glCreateProgram();
}

void ShaderProgram::link()
{
    glLinkProgram(shaderProgramID);
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &successfulLink);
    if (successfulLink == GL_FALSE) {
        glGetProgramInfoLog(shaderProgramID, INFOSIZE, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgramID);
    successfulUse = GL_TRUE;
}

GLint ShaderProgram::isLinked() const
{
    return successfulLink;
}

GLint ShaderProgram::isUsed() const
{
    return successfulUse;
}

GLuint ShaderProgram::getShaderProgramID() const
{
    return shaderProgramID;
}

GLchar* ShaderProgram::getInfoLog()
{
    return infoLog;
}

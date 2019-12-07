//
// Created by maxkile on 07.12.2019.
//
#pragma once

#include <iostream>
#include "base/stdafx.hpp"
#include "base/Constants.hpp"

class ShaderProgram {

    GLuint shaderProgram;
    GLchar infoLog[INFOSIZE];

    GLint successfulLink;
    GLint successfulUse;

    template<typename T>
    void attachShaders(T& first)
    {
        glAttachShader(shaderProgram,first);
    }

public:
    explicit ShaderProgram();

    template <typename T, typename... Args>
    void attachShaders(T& first, Args& ...args)
    {
        glAttachShader(shaderProgram,first);
        attachShaders(args...);
    }

    void link();

    void use();

    GLint isLinked() const;

    GLint isUsed() const;

    GLchar* getInfoLog();

};
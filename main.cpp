#include <stdio.h>
#include <GL/glew.h>
#include <iostream>
#include "functions.hpp"

#define GLEW_STATIC
#include <GLFW/glfw3.h>


int main()
{
    glfwInit();//init glfw context

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//version of glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//old functions will cause errors
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800,600,"HELLO", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Error" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    GLint x,y;
    glfwGetFramebufferSize(window,&x,&y);//retrieve framebuffersize(in pixels) from window
    glViewport(0,0,x,y);//set viewport
    glewExperimental = GL_TRUE;
    if (glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
//    glfwShowWindow(window);
    glfwTerminate();//terminate glfw context
}

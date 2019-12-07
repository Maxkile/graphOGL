//
// Created by maxkile on 02.12.2019.
//

#include "../include/Callbacks.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
    // и приложение после этого закроется
    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
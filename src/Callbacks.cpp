//
// Created by maxkile on 02.12.2019.
//

#include "../include/Callbacks.hpp"

void callbacks::exit_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

}

//void callbacks::change_alpha_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
//    {
//        alpha += 0.1f;
//        if (alpha >= 1.0f)
//            alpha = 1.0f;
//    }
//    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
//    {
//        alpha -= 0.1f;
//        if (alpha <= 0.0f)
//            alpha = 0.0f;
//    }
//}
void callbacks::fullscreen_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
//    m_window = glfwCreateWindow(width, height, m_caption.c_str(),
//                                fullScreen ? m_monitor : NULL, m_window);
//    if (key == GLFW_KEY_F12 && action == GLFW_PRESS)
//    {
//        glfwSetWindowSize(GLFW_MAXIMIZED)
//    }
}
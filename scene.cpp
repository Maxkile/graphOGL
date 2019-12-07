

#include <iostream>
#include <cmath>

#include "include/Callbacks.hpp"
#include "include/Shader.hpp"
#include "include/ShaderProgram.hpp"


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

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    GLint x,y;
    glfwGetFramebufferSize(window,&x,&y);//retrieve framebuffersize(in pixels) from window
    glViewport(0,0,x,y);//set viewport

    glfwSetKeyCallback(window,key_callback);//register before loop and after windows definition


    /*
     * Vertex Shader
     */

    Shader shader;

    shader.readSourceToString("../shaders/vertex.glsl");
    shader.compile(GL_VERTEX_SHADER);
    GLuint vertexShaderID = shader.getCustomShaderID();//just an id, simply can copy it

    /*
     * Fragment Shader
     */
    shader.readSourceToString("../shaders/fragment.glsl");
    shader.compile(GL_FRAGMENT_SHADER);
    GLint fragmentShaderID = shader.getCustomShaderID();

    /*
     * Create shader program
     */
    ShaderProgram shaderProgram;
    shaderProgram.attachShaders(vertexShaderID, fragmentShaderID);
    shaderProgram.link();

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);


    /*
 * Vertex Array Object specifies currebt context of VBO, pointers and other. In other words, it's just like settings array.
 */
    GLuint vertexArrayID,vertexBufferID;

    glGenBuffers(1,&vertexBufferID);//generate buffer(name)
    glGenVertexArrays(1, &vertexArrayID);//generate vertex array object(name)

    glBindVertexArray(vertexArrayID);
    // Bind the Vertex Array Object FIRST, then bind and set vertex buffer(s) and attribute pointer(s).

    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);//bind all calls to GL_ARRAY_BUFFER to work with VBO(change condition of GL_ARRAY_BUFFER)
    GLfloat triangle_verts[] =
        {
            -0.5f,-0.5f,0.0f,
            0.5f,-0.5f,0.0f,
            0.0f,0.5f,0.0f
        };

    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle_verts),triangle_verts,GL_STATIC_DRAW);//set data


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);//set pointers
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
    glBindVertexArray(0);//unbind

    /*
     * Shader markup for opengl
     */



    //need to load source from file

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);//use condition

        shaderProgram.use();

        glBindVertexArray(vertexShaderID);//bind
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);//unbind


        glfwSwapBuffers(window);
    }
    glfwShowWindow(window);

    glDeleteVertexArrays(1,&vertexArrayID);
    glDeleteBuffers(1,&vertexBufferID);

    glfwTerminate();//terminate glfw context
}

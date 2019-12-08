

#include <iostream>

#include "include/Callbacks.hpp"
#include "include/Shader.hpp"
#include "include/ShaderProgram.hpp"
#include <glm/glm.hpp>

int main()
{
    glfwInit();//init glfw context

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//version of glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//old functions will cause errors
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800,600,"Scene", nullptr, nullptr);
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

    glfwSetKeyCallback(window,callbacks::exit_callback);//register before loop and after windows definition


    /*
     * Vertex Shader
     */

    Shader shader1;
    ShaderProgram shaderProgram1;
    shader1.readSourceToString("../shaders/vertex.glsl");
    shader1.compile(GL_VERTEX_SHADER);
    GLuint vertexShaderID1 = shader1.getCustomShaderID();//just an id, simply can copy it

    shader1.readSourceToString("../shaders/fragment1.glsl");
    shader1.compile(GL_FRAGMENT_SHADER);
    GLint fragmentShaderID1 = shader1.getCustomShaderID();

    shaderProgram1.attachShaders(vertexShaderID1, fragmentShaderID1);
    shaderProgram1.link();



    Shader shader2;
    ShaderProgram shaderProgram2;
    shader2.readSourceToString("../shaders/vertex.glsl");
    shader2.compile(GL_VERTEX_SHADER);
    GLuint vertexShaderID2 = shader2.getCustomShaderID();//just an id, simply can copy it

    shader2.readSourceToString("../shaders/fragment2.glsl");
    shader2.compile(GL_FRAGMENT_SHADER);
    GLint fragmentShaderID2 = shader2.getCustomShaderID();
    /*
     * Create shader program
     */
    shaderProgram2.attachShaders(vertexShaderID2, fragmentShaderID2);
    shaderProgram2.link();

    glDeleteShader(vertexShaderID1);
    glDeleteShader(vertexShaderID2);
    glDeleteShader(fragmentShaderID1);
    glDeleteShader(fragmentShaderID2);

    /*
 * Vertex Array Object specifies currebt context of VBO, pointers and other. In other words, it's just like settings array.
 */
    GLuint vertexArrayIDs[2],vertexBufferIDs[2];
//    GLuint indexBufferID;//for EBO

    glGenBuffers(2,vertexBufferIDs);//generate 1(some) name for buffer(name)
//    glGenBuffers(1,&indexBufferID);//generate 1(some) name for buffer of indices(name)
    glGenVertexArrays(2, vertexArrayIDs);//generate 1(some) vertex array for object(name)

    GLfloat firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f
    };
    GLfloat secondTriangle[] = {
        0.0f, -0.5f, 0.0f,
        0.9f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f
    };

    glBindVertexArray(vertexArrayIDs[0]);//bind VAO(now saving context)
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferIDs[0]);//bind all calls to GL_ARRAY_BUFFER to work with VBO(change condition of GL_ARRAY_BUFFER)
    glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle),firstTriangle,GL_STATIC_DRAW);//set data
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);//!!! set pointers to vertex attributes(VAO)
    glEnableVertexAttribArray(0);//enable vertex attribute array from (this) position
    glBindVertexArray(0);//unbind VAO context

    glBindVertexArray(vertexArrayIDs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferIDs[1]);//bind all calls to GL_ARRAY_BUFFER to work with VBO(change condition of GL_ARRAY_BUFFER)
    glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);//set data
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);//!!! set pointers to vertex attributes(VAO)
    glEnableVertexAttribArray(0);//enable vertex attribute array from (this) position
    glBindVertexArray(0);//unbind VAO context


    //!!! Bind the Vertex Array Object FIRST, then bind and set vertex buffer(s) and attribute pointer(s).

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferID);//bind all calls to GL_ELEMENT_ARRAY_BUFFER to work with IBO(change condition of GL_ARRAY_BUFFER)

    //    GLfloat triangle_verts[] =
//        {
//            -0.5f,-0.5f,0.0f,
//            0.5f,-0.5f,0.0f,
//            -0.5f,0.5f,0.0f,
//            0.5f,0.5f,0.0f
//        };
//    GLbyte indices[] =
//        {
//            0,1,3,
//            0,2,3
//        };

//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);//set indices for drawing

    glPolygonMode(GL_BACK, GL_FILL);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();//processing events from event queue
        glClearColor(0.5f,0.5f,0.75f,1.0f);//setting GL_COLOR_BUFFERED_BIT
        glClear(GL_COLOR_BUFFER_BIT);//use condition

        GLfloat time = glfwGetTime();
        GLint vertexColorLocation;
        GLfloat red,green,blue;

        shaderProgram1.use();

        red = (cos(time) / 2) + 0.2;
        green = (cos(time) / 2) + 0.3;
        blue = (cos(time) / 2) + 0.4;

        //using uniform vec4 in fragment shader

        vertexColorLocation = glGetUniformLocation(shaderProgram1.getShaderProgramID(),"color");
        glUniform4f(vertexColorLocation,red,green,blue,1.0f);//set uniform buffer

        glBindVertexArray(vertexArrayIDs[0]);//bind
        glDrawArrays(GL_TRIANGLES, 0, 3);//draw from "data" in VBO
        glBindVertexArray(0);//unbind

        shaderProgram2.use();

        red = (sin(time) / 2) + 0.2;
        green = (sin(time) / 2) + 0.3;
        blue = (sin(time) / 2) + 0.4;

        vertexColorLocation = glGetUniformLocation(shaderProgram2.getShaderProgramID(),"color");
        glUniform4f(vertexColorLocation,red,green,blue,1.0f);//set uniform buffer

        glBindVertexArray(vertexArrayIDs[1]);//bind
        glDrawArrays(GL_TRIANGLES, 0, 3);//draw from "data" in VBO
        glBindVertexArray(0);//unbind
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);//draw from indices from EBO binded to VAO


        glfwSwapBuffers(window);
    }
    glfwShowWindow(window);

    glDeleteVertexArrays(2,vertexArrayIDs);
    glDeleteBuffers(2,vertexBufferIDs);

    glfwTerminate();//terminate glfw context
}

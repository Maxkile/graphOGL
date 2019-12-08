

#include <iostream>

#include "include/Callbacks.hpp"
#include "include/Shader.hpp"
#include "include/ShaderProgram.hpp"
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>

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


//    //XYZ RGB XY(texture)
//    GLfloat multiColorTriangle[] = {
//        -0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
//        -0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.9f, 0.0f,
//        -0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.45f, 0.5f
//    };

    //XYZ RGB XY(texture)
    GLfloat square_verts[] =
        {
            0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f
        };

    GLubyte indices[] =
    {
        0,1,3,
        1,2,3
    };
//
//    GLfloat secondTriangle[] = {
//        0.0f, -0.5f, 0.0f,
//        0.9f, -0.5f, 0.0f,
//        0.45f, 0.5f, 0.0f
//    };

    /*
     * Shaders(vertex and fragment: geometric don't have to)
     */

    Shader shader1;
    ShaderProgram shaderProgram1;
    shader1.readSourceToString("../shaders/vertex/vertexWithColor.glsl");
    shader1.compile(GL_VERTEX_SHADER);
    GLuint vertexShaderID1 = shader1.getCustomShaderID();//just an id, simply can copy it

    shader1.readSourceToString("../shaders/fragment/multiColorFragment.glsl");
    shader1.compile(GL_FRAGMENT_SHADER);
    GLint fragmentShaderID1 = shader1.getCustomShaderID();

    shaderProgram1.attachShaders(vertexShaderID1, fragmentShaderID1);
    shaderProgram1.link();

    glDeleteShader(vertexShaderID1);
    glDeleteShader(fragmentShaderID1);


//    Shader shader2;
//    ShaderProgram shaderProgram2;
//    shader2.readSourceToString("../shaders/vertex/vertex.glsl");
//    shader2.compile(GL_VERTEX_SHADER);
//    GLuint vertexShaderID2 = shader2.getCustomShaderID();//just an id, simply can copy it
//
//    shader2.readSourceToString("../shaders/fragment/fragment.glsl");
//    shader2.compile(GL_FRAGMENT_SHADER);
//    GLint fragmentShaderID2 = shader2.getCustomShaderID();
//
//    shaderProgram2.attachShaders(vertexShaderID2, fragmentShaderID2);
//    shaderProgram2.link();
//
//    glDeleteShader(vertexShaderID1);//best practice
//    glDeleteShader(vertexShaderID2);
//    glDeleteShader(fragmentShaderID1);
//    glDeleteShader(fragmentShaderID2);

    /*
 * Vertex Array Object specifies currebt context of VBO, pointers and other. In other words, it's just like settings array.
 */
//    GLuint indexBufferID;//for EBO

    GLuint indexBufferID,vertexBufferID,vertexArrayID;
    glGenBuffers(1,&indexBufferID);
    glGenBuffers(1,&vertexBufferID);//generate 1(some) name for buffer(name)
    glGenVertexArrays(1, &vertexArrayID);//generate 1(some) vertex array for object(name)

    glBindVertexArray(vertexArrayID);//bind VAO(now saving context)

    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);//bind all calls to GL_ARRAY_BUFFER to work with VBO(change condition of GL_ARRAY_BUFFER)
    glBufferData(GL_ARRAY_BUFFER,sizeof(square_verts),square_verts,GL_STATIC_DRAW);//set data

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferID);//bind all calls to GL_ELEMENT_ARRAY_BUFFER to work with IBO(change condition of GL_ARRAY_BUFFER)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);//set indices for drawing

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)0);//!!! set pointers to vertex attributes(VAO)
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));//!!! set pointers to vertex attributes(VAO)(color)
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat),(GLvoid*)(6 * sizeof(GLfloat)));//!!! set pointers to vertex attributes(VAO)(texture)
    glEnableVertexAttribArray(0);//enable this vertex attrib pointer(with ID = 0)
    glEnableVertexAttribArray(1);//enable this vertex attrib pointer(with ID = 1)
    glEnableVertexAttribArray(2);//enable this vertex attrib pointer(with ID = 2)
    glBindVertexArray(0);//unbind VAO context

//    glBindVertexArray(vertexArrayIDs[1]);
//    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferIDs[1]);//bind all calls to GL_ARRAY_BUFFER to work with VBO(change condition of GL_ARRAY_BUFFER)
//    glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);//set data
//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);//!!! set pointers to vertex attributes(VAO)
//    glEnableVertexAttribArray(0);//enable this vertex attrib pointer(with ID = 1)
//    glBindVertexArray(0);//unbind VAO context


    //!!! Bind the Vertex Array Object FIRST, then bind and set vertex buffer(s) and attribute pointer(s).


    /*
     * Textures generating and binding
     */

    GLuint textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int texWidth,texHeight;
    unsigned char* textureImage = SOIL_load_image("../resources/textures/stone.png",&texWidth,&texHeight,0,SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    std::cout << SOIL_last_result()  << std::endl;
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(textureImage);
    glBindTexture(GL_TEXTURE_2D, 0);//best practice

//    glPolygonMode(GL_BACK, GL_FILL);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();//processing events from event queue
        glClearColor(0.2f,0.2f,0.2f,1.0f);//setting GL_COLOR_BUFFERED_BIT
        glClear(GL_COLOR_BUFFER_BIT);//use condition



        shaderProgram1.use();
        //using uniform vec4 in fragment shader

        glBindTexture(GL_TEXTURE_2D,textureID);
        glBindVertexArray(vertexArrayID);//bind
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
        glBindVertexArray(0);//unbind

//        shaderProgram2.use();
//        GLfloat time = glfwGetTime();
//        GLint vertexColorLocation;
//        GLfloat red,green,blue;
//        red = (sin(time) / 2) + 0.2;
//        green = (sin(time) / 2) + 0.3;
//        blue = (sin(time) / 2) + 0.4;
//
//        vertexColorLocation = glGetUniformLocation(shaderProgram2.getShaderProgramID(),"color");
//        glUniform4f(vertexColorLocation,red,green,blue,1.0f);//set uniform buffer
//
//        glBindVertexArray(vertexArrayIDs[1]);//bind
//        glDrawArrays(GL_TRIANGLES, 0, 3);//draw from "data" in VBO
//        glBindVertexArray(0);//unbind

//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,0);//draw from indices from EBO binded to VAO


        glfwSwapBuffers(window);
    }
    glfwShowWindow(window);

    glDeleteVertexArrays(1,&vertexArrayID);
    glDeleteBuffers(1,&vertexBufferID);

    glfwTerminate();//terminate glfw context
}

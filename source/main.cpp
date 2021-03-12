#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "object.hpp"
#include "utils.hpp"
#include "camera.hpp"

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 ourColor;\n"
                                 "uniform mat4 model;\n"
                                 "uniform mat4 view;\n"
                                 "uniform mat4 projection;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                                 "   ourColor = aColor;\n"
                                 "}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(ourColor, 1.0f);\n"
                                   "}\n\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
int processInput(GLFWwindow *, int &, Camera &, glm::mat4 &, Object[]);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // how to handle the windows n all are done with this
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 0", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers connect to opengl implementaion from driver
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    Object objects[] = {createDecagonalPrism(), createHexDiPyramid(), createSqPyramid()};
    int cur = 0;
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // first parameter is for number of buffer objects to create
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    objects[cur].bindBuffer(VAO, VBO);

    // as we only have a single shader, we could also just activate our shader once beforehand if we want to
    glUseProgram(shaderProgram);

    //glm stuff
    Camera cam;
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    objects[cur].applyMVP(shaderProgram, cam, projection);
    float ch = -0.01;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        int pressed = processInput(window, cur, cam, projection, objects);
        if (pressed)
        {
            objects[cur].applyMVP(shaderProgram, cam, projection);
            objects[cur].bindBuffer(VAO, VBO);
        }
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        objects[cur].draw(VAO);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
int processInput(GLFWwindow *window, int &cur, Camera &cam, glm::mat4 &projection, Object objects[])
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && cur != 0)
        cur = 0;
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && cur != 1)
        cur = 1;
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && cur != 2)
        cur = 2;
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        objects[cur].moveXn();
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        objects[cur].moveXp();
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        objects[cur].moveYn();
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        objects[cur].moveYp();
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        objects[cur].moveZn();
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        objects[cur].moveZp();
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        objects[cur].rotate();
    else if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        cam.moveYn();
    else if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        cam.moveYp();
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cam.moveXn();
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cam.moveXp();
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cam.moveZn();
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cam.moveZp();
    else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
    }
    else
        return 0;
    return 1;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
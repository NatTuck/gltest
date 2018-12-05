
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <assert.h>

#include <GLFW/glfw3.h>

#include "shaders.h"

void
render(GLFWwindow* window, int sp, int vao)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(sp);
    glBindVertexArray(vao);
    glPointSize(40);
    glDrawArrays(GL_POINTS, 0, 3);

    glfwSwapBuffers(window);
}

void
on_glfw_error(int error, const char* desc)
{
    printf("glfw error: %d (%s)\n", error, desc);
}

void
on_framebuffer_resize(GLFWwindow* _window, int width, int height)
{
    printf("Resize: %d %d\n", width, height);
    glViewport(0, 0, width, height);
}

int
main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    glfwSetErrorCallback(on_glfw_error);
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set up the context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, on_framebuffer_resize);
    glViewport(0, 0, 800, 600);

    int sp = compile_shader_program(
        "shaders/vertex.glsl",
        "shaders/fragment.glsl");

    static float points[] = {
        0.3f, 0.3f,
        0.5f, 0.5f,
        -0.7f, 0.7f
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), points, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        render(window, sp, vao);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


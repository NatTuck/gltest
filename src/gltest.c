
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

    // Prep the window

    // OpenGL ES
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "gltest window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set up the context */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, on_framebuffer_resize);
    glViewport(0, 0, 800, 600);

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int sp = compile_shader_program(
        "shaders/vertex.glsl",
        "shaders/fragment.glsl");

    static float points[] = {
        0.3f, 0.3f,  1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
        -0.7f, 0.7f, 0.0f, 0.0f, 1.0f, 1.0f,
    };

    unsigned int vao[16];
    glGenVertexArrays(16, vao);
    glBindVertexArray(vao[0]);

    unsigned int vbo[16];
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), points, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        render(window, sp, vao[0]);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


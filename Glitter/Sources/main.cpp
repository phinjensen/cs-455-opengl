// Local Headers
#include "glm/fwd.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "glitter.hpp"
#include "ShaderHelpers.h"
#include "ModelLoader.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);

	// **************************************
	// Setup Vertex arrays here
	// **************************************
    GLuint my_shader = LoadProgram("/home/phin/CS 455/Glitter/Glitter/Shaders/basic.vert", "/home/phin/CS 455/Glitter/Glitter/Shaders/basic.frag");

    GLuint VAO;
    GLuint VBO;
    float vertices[] = {
        -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
    };

    int triangles = 3;

    glGenVertexArrays(triangles, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, triangles * (9 + 9) * sizeof(float), vertices, GL_STATIC_DRAW);

    GLint position = glGetAttribLocation(my_shader, "position");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    GLint color = glGetAttribLocation(my_shader, "ColorIn");
    glEnableVertexAttribArray(color);
    glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	// **************************************
	
    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// **********************************
		// Add rendering code here
        glUseProgram(my_shader);
        glDrawArrays(GL_TRIANGLES, 0, triangles * 3);
		// **********************************

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();

    return EXIT_SUCCESS;
}

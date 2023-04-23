#include "vendors/GLFW/glfw3.h"
#include <stdio.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
//#include "vendors/third-party/include/serial/serial.h"
//#include "third-party/include/serial/serial.h"
#include "vendors/SERIAL/serial.h"

int main() {
    GLFWwindow* window;

    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a window and a context
    window = glfwCreateWindow(1000, 600, "My Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw a cube with grid lines on the left
        glViewport(0, 0, 500, 600);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
         glRotatef(glfwGetTime() * 50.0f, 0.0f, 1.0f, 0.0f); 
        float size = 2.0f;
        float spacing = 10.0f;
        int num_lines = 10;
        float start = -size / 2.0f;
        float end = size / 2.0f;

        // Draw the grid lines
glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_LINES);
for (int i = 0; i <= num_lines; i++) {
    float x = start + (i * (size / num_lines));
    float y = start + (i * (size / num_lines));
    float z = start + (i * (size / num_lines));
    // X-axis lines
    glVertex3f(x, start, start);
    glVertex3f(x, end, start);
    glVertex3f(x, start, end);
    glVertex3f(x, end, end);
    // Y-axis lines
    glVertex3f(start, x, start);
    glVertex3f(end, x, start);
    glVertex3f(start, x, end);
    glVertex3f(end, x, end);
    // Z-axis lines
    glVertex3f(start, start, x);
    glVertex3f(end, start, x);
    glVertex3f(start, end, x);
    glVertex3f(end, end, x);

    // Lines along the faces of the cube
    glVertex3f(x, start, start);
    glVertex3f(x, start, end);
    glVertex3f(x, end, start);
    glVertex3f(x, end, end);
    glVertex3f(start, x, start);
    glVertex3f(start, x, end);
    glVertex3f(end, x, start);
    glVertex3f(end, x, end);
    glVertex3f(start, start, x);
    glVertex3f(start, end, x);
    glVertex3f(end, start, x);
    glVertex3f(end, end, x);
}
glEnd();
        // Draw the wireframe cube
        glColor3f(1.0f, 1.0f, 1.0f);
        glutWireCube(size);

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();
    return 0;
}

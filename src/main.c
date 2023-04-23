#include "vendors/GLFW/glfw3.h"
#include <stdio.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "vendors/SERIAL/serial_port.h"
#include <math.h>
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


  /*
    //
    SerialPort port;
    const char* port_name = "/dev/tty.usbserial-A9007UX1";  // Change this to the correct port name
    speed_t baudrate = 9600;
    SerialPort_init(&port, port_name, baudrate);

     Check if the object was created successfully
    if (SerialPort_get_fd(&port) == -1) {
      return 1;
    }

  
     // use the serial_port object to read and write data
    char buffer[256];
    int bytes_read = SerialPort_read(&serial_port, buffer, sizeof(buffer));
    printf("Read %d bytes: %s\n", bytes_read, buffer);

    const char* message = "Hello, world!";
    int bytes_written = SerialPort_write(&serial_port, message, strlen(message));
    printf("Wrote %d bytes\n", bytes_written);

    SerialPort_destroy(&serial_port);*/


 // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Set viewport to the entire window
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glViewport(0, 0, window_width, window_height);

    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)window_width / (float)window_height, 0.1f, 1000.0f);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   gluLookAt(50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glScalef(1.5f, 1.5f, 1.5f);
    glRotatef(glfwGetTime() * 50.0f, 0.0f, 1.0f, 0.0f);
    // Draw the grid lines
    float size = 20.0f;
    float step = 1.0f;

      // Draw the origin point
    glPointSize(10.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    // Draw the XY plane
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (float i = -size; i <= size; i += step) {
        glVertex3f(i, -size, 0.0f);
        glVertex3f(i, size, 0.0f);
        glVertex3f(-size, i, 0.0f);
        glVertex3f(size, i, 0.0f);
    }
    glEnd();

    // Draw the XZ plane
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for (float i = -size; i <= size; i += step) {
        glVertex3f(i, 0.0f, -size);
        glVertex3f(i, 0.0f, size);
        glVertex3f(0.0f, -size, i);
        glVertex3f(0.0f, size, i);
    }
    glEnd();

    // Draw the YZ plane
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
    for (float i = -size; i <= size; i += step) {
        glVertex3f(0.0f, i, -size);
        glVertex3f(0.0f, i, size);
        glVertex3f(-size, 0.0f, i);
        glVertex3f(size, 0.0f, i);
    }
    glEnd();

    // Swap buffers
    glfwSwapBuffers(window);

    // Poll for events
    glfwPollEvents();
}





    // Clean up
    glfwTerminate();
    return 0;
}

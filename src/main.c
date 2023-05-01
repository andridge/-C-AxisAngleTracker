#include "vendors/GLFW/glfw3.h"
#include <stdio.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "vendors/SERIAL/serial_port.h"
#include <math.h>
#define BUFFER_SIZE 256

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

SerialPort port;
const char* port_name = "/dev/tty.usbserial-110";  // Change this to the correct port name
speed_t baudrate = 9600;
SerialPort_init(&port, port_name, baudrate);

// Check if the object was created successfully
if (SerialPort_get_fd(&port) == -1) {
  return 1;
}

char buffer[BUFFER_SIZE];
int bytes_read;
float total_angle_x ;
float total_angle_y ;
int x;
int y;
 // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Set swap interval to 1 millisecond
    glfwSwapInterval(5);
    //
   //
     // Read data from the serial port
    bytes_read = SerialPort_read(&port, buffer, BUFFER_SIZE);

    if (bytes_read > 0) {
      //  printf("Total Angle X & Y: %f\n",buffer);
     sscanf(buffer, "%*s %*s %f %*s %*s %*s %f", &total_angle_x, &total_angle_y);
    x = round(total_angle_x);
    y = round(total_angle_y);
    printf("Total Angle X: %d\n", x);
    printf("Total Angle Y: %d\n", y);

    }

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

    glScalef(5.5f, 5.5f, 5.5f);
   //glRotatef(glfwGetTime() * 50.0f, 0.0f, 1.0f, 0.0f);
    // Set the object coordinates
    float object_x = 3.5f;
    float object_y = 3.5f;
    // Set the color of the square
    glColor3f(1.0f, 0.0f, 1.0f); // purple color (red and blue)
    //
   
// Inside your main loop, before drawing the cube, update the object position with the previous rotations
glPushMatrix();
glTranslatef(object_x, 2.5f, object_y); // set the object's position and lift it by 0.5 units along the y-axis
glRotatef(y, 0.0f, 1.0f, 0.0f); // apply previous y rotation
glRotatef(x, 1.0f, 0.0f, 0.0f); // apply previous x rotation

    // Draw bottom square
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, -0.5f); // bottom left corner
    glVertex3f(0.5f, 0.0f, -0.5f); // bottom right corner
    glVertex3f(0.5f, 0.0f, 0.5f); // top right corner
    glVertex3f(-0.5f, 0.0f, 0.5f); // top left corner
    glEnd();

    // Draw top square
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 1.0f, -0.5f); // bottom left corner
    glVertex3f(0.5f, 1.0f, -0.5f); // bottom right corner
    glVertex3f(0.5f, 1.0f, 0.5f); // top right corner
    glVertex3f(-0.5f, 1.0f, 0.5f); // top left corner
    glEnd();

    // Draw connecting lines
    glBegin(GL_LINES);
    glVertex3f(-0.5f, 0.0f, -0.5f); // bottom left corner
    glVertex3f(-0.5f, 1.0f, -0.5f); // top left corner

    glVertex3f(0.5f, 0.0f, -0.5f); // bottom right corner
    glVertex3f(0.5f, 1.0f, -0.5f); // top right corner

    glVertex3f(0.5f, 0.0f, 0.5f); // top right corner
    glVertex3f(0.5f, 1.0f, 0.5f); // bottom right corner

    glVertex3f(-0.5f, 0.0f, 0.5f); // top left corner
    glVertex3f(-0.5f, 1.0f, 0.5f); // bottom left corner
    glEnd();

    glPopMatrix();


    // Draw your object here
    // Draw the X axis
    glColor3f(1.0f, 0.0f, 0.0f); // red color
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // starting point
    glVertex3f(5.0f, 0.0f, 0.0f); // ending point
    glEnd();

    // Draw the Y axis
    glColor3f(0.0f, 1.0f, 0.0f); // green color
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // starting point
    glVertex3f(0.0f, 5.0f, 0.0f); // ending point
    glEnd();

    // Draw the Z axis
    glColor3f(0.0f, 0.0f, 1.0f); // blue color
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // starting point
    glVertex3f(0.0f, 0.0f, 5.0f); // ending point
    glEnd();
    // Draw the grid lines on the XY plane
    glColor3f(0.5f, 0.5f, 0.5f); // set the color to gray
    glBegin(GL_LINES); // start drawing lines
    for(float i=1.0f; i<=5.0f; i+=1.0f) { // loop through the x and y values
        glVertex3f(i, 0.0f, 0.0f); // set the starting point of a line on the x-axis
        glVertex3f(i, 5.0f, 0.0f); // set the ending point of a line on the x-axis
        glVertex3f(0.0f, i, 0.0f); // set the starting point of a line on the y-axis
        glVertex3f(5.0f, i, 0.0f); // set the ending point of a line on the y-axis
    }
    glEnd(); // end drawing lines


    // Draw the grid lines on the XZ plane
    glBegin(GL_LINES); // start drawing lines
    for(float i=1.0f; i<=5.0f; i+=1.0f) { // loop through the x and z values
        glVertex3f(i, 0.0f, 0.0f); // set the starting point of a line on the x-axis
        glVertex3f(i, 0.0f, 5.0f); // set the ending point of a line on the x-axis
        glVertex3f(0.0f, 0.0f, i); // set the starting point of a line on the z-axis
        glVertex3f(5.0f, 0.0f, i); // set the ending point of a line on the z-axis
    }
    glEnd(); // end drawing lines

    // Draw the grid lines on the YZ plane
    glBegin(GL_LINES); // start drawing lines
    for(float i=1.0f; i<=5.0f; i+=1.0f) { // loop through the y and z values
        glVertex3f(0.0f, i, 0.0f); // set the starting point of a line on the y-axis
        glVertex3f(0.0f, i, 5.0f); // set the ending point of a line on the y-axis
        glVertex3f(0.0f, 0.0f, i); // set the starting point of a line on the z-axis
        glVertex3f(0.0f, 5.0f, i); // set the ending point of a line on the z-axis
    }
    glEnd(); // end drawing lines
    SerialPort_flush(&port);
    //
    // Swap buffers
    glfwSwapBuffers(window);

    // Poll for events
    glfwPollEvents();
}
    // Clean up
    glfwTerminate();
    return 0;
}

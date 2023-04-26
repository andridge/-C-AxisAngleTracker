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


    /*
    //
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
    float total_angle_x = 0.0f;
    float total_angle_y = 0.0f;

    while (1) {
        // Read data from the serial port
        bytes_read = SerialPort_read(&port, buffer, BUFFER_SIZE);

        if (bytes_read > 0) {
            // Print the data received
         // printf("Data received: %s\n", buffer);
           float total_angle_x, total_angle_y;
             sscanf(buffer, "Total Angle X: %f Total Angle Y: %f", &total_angle_x, &total_angle_y);
           // renderText(10, 10, buffer);
            // Set the position for displaying the text
          // glWindowPos2f(10, 10);

            // Render the text
       //   glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)buffer);
        }

        // Wait for 5 seconds
        usleep(100000);
    }

    SerialPort_destroy(&port);*/
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
float total_angle_x = 0.0f;
float total_angle_y = 0.0f;

// Enable face culling


 // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    //
     // Read data from the serial port
    bytes_read = SerialPort_read(&port, buffer, BUFFER_SIZE);

    if (bytes_read > 0) {
        // Print the data received
        float total_angle_x;
        float total_angle_y;
      //  printf("Total Angle X & Y: %f\n",buffer);
  sscanf(buffer, "Total Angle X: %f Total Angle Y: %f", &total_angle_x, &total_angle_y);

        printf("Total Angle X: %f\n",total_angle_x);
        printf("Total Angle Y: %f\n",total_angle_y);
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

    glScalef(4.5f, 4.5f, 4.5f);
  // glRotatef(glfwGetTime() * 50.0f, 0.0f, 1.0f, 0.0f);
    // Draw the grid lines
    //float size = 20.0f;
    //float step = 1.0f;
        //
// Calculate the rotation angles from the orientation values
float rotate_x = total_angle_x * M_PI / 180.0f;
float rotate_y = total_angle_y * M_PI / 180.0f;

// Apply rotation transformations
glRotatef(rotate_x, 1.0f, 0.0f, 0.0f); // rotate around the x-axis
glRotatef(rotate_y, 0.0f, 1.0f, 0.0f); // rotate around the y-axis

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



    
    // Swap buffers
    glfwSwapBuffers(window);

    // Poll for events
    glfwPollEvents();
}





    // Clean up
    glfwTerminate();
    return 0;
}

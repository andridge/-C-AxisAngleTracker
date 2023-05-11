#include "serial_port.h"
#include <pthread.h>
#include <stdio.h>

#define BUFFER_SIZE 256

// Declare global variables for shared data
char buffer[BUFFER_SIZE];
int bytes_read;
float total_angle_x ;
float total_angle_y ;
float latitude;
float longitude;
extern pthread_mutex_t data_mutex;
// Define a smoothing factor
//const float SMOOTHING_FACTOR = 0.1f;

// Define a mutex for protecting shared data
//pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

void *serial_thread(void *arg) {
    SerialPort port;
    const char* port_name = "/dev/tty.usbserial-130";  // Change this to the correct port name
    speed_t baudrate = 9600;
    SerialPort_init(&port, port_name, baudrate);

    // Check if the object was created successfully
    if (SerialPort_get_fd(&port) == -1) {
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Loop indefinitely
    while (1) {
        // Read data from the serial port
        bytes_read = SerialPort_read(&port, buffer, BUFFER_SIZE);

        if (bytes_read > 0) {
            float x, y, lat, lon;
            sscanf(buffer, "%*s %*s %f %*s %*s %*s %f %f %f ", &x, &y, &lat, &lon);

            // Acquire the mutex before updating shared data
            pthread_mutex_lock(&data_mutex);

            total_angle_x = x;
            total_angle_y = y;
            latitude = lat;
            longitude = lon;

            // Release the mutex after updating shared data
            pthread_mutex_unlock(&data_mutex);
        }
    }

    // Close the serial port when done
  //  SerialPort_close(&port);

    return NULL;
}

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

typedef struct {
    int fd_;
} SerialPort;

void SerialPort_init(SerialPort* port, const char* port_name, speed_t baudrate);
void SerialPort_destroy(SerialPort* port);
int SerialPort_read(SerialPort* port, void* buffer, size_t size);
int SerialPort_write(SerialPort* port, const void* data, size_t size);
int SerialPort_get_fd(const SerialPort* port);

#endif // SERIAL_PORT_H

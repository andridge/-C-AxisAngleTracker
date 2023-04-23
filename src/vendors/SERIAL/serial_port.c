#include "serial_port.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void SerialPort_init(SerialPort* port, const char* port_name, speed_t baudrate) {
    port->fd_ = open(port_name, O_RDWR | O_NOCTTY | O_NDELAY);

    if (port->fd_ == -1) {
        perror("SerialPort: Unable to open port");
        return;
    }

    struct termios options;
    tcgetattr(port->fd_, &options);
    cfsetispeed(&options, baudrate);
    cfsetospeed(&options, baudrate);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_oflag &= ~OPOST;
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 100;

    if (tcsetattr(port->fd_, TCSANOW, &options) < 0) {
        perror("SerialPort: Unable to set serial port attributes");
        close(port->fd_);
        port->fd_ = -1;
        return;
    }
}

void SerialPort_destroy(SerialPort* port) {
    if (port->fd_ != -1) {
        close(port->fd_);
        port->fd_ = -1;
    }
}

int SerialPort_read(SerialPort* port, void* buffer, size_t size) {
    if (port->fd_ == -1) {
        return -1;
    }

    ssize_t n = read(port->fd_, buffer, size);
    if (n < 0) {
        perror("SerialPort: Error reading from serial port");
    }
    return n;
}

int SerialPort_write(SerialPort* port, const void* data, size_t size) {
    if (port->fd_ == -1) {
        return -1;
    }

    ssize_t n = write(port->fd_, data, size);
    if (n < 0) {
        perror("SerialPort: Error writing to serial port");
    }
    return n;
}

int SerialPort_get_fd(const SerialPort* port) {
    return port->fd_;
}

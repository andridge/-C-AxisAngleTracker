APP_NAME = openseasons
BUILD_DIR = ./bin
C_FILES = ./src/*.c ./src/vendors/SERIAL/serial_port.c

APP_DEFINES:=
APP_INCLUDES:= -I./src/vendors/GLFW -I./src/vendors/SERIAL -framework Cocoa -framework IOKit -framework OpenGL -framework GLUT 
APP_LINKERS:= -L./src/vendors/GLFW/lib -lglfw3 -L/opt/homebrew/Cellar/libserialport/0.1.1/lib -lserialport -framework OpenGL -framework GLUT

build:
	clang $(C_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES) $(APP_LINKERS)

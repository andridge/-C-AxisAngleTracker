APP_NAME = openseasons
BUILD_DIR = ./bin
C_FILES = ./src/*.c

APP_DEFINES:=
APP_INCLUDES:= -I./src/vendors/GLFW  -framework Cocoa -framework IOKit -framework OpenGL -framework GLUT 
APP_LINKERS:= -L./src/vendors/GLFW/lib -lglfw3 -framework OpenGL -framework GLUT
build:
	clang $(C_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES) $(APP_LINKERS)  

#Version 1.2 - 06-06-2020
#Makefile for Windows and Linux developed by Cristobal Medrano Alvarado.
#Makefile para Windows y Linux desarrollado por Cristobal Medrano Alvardo.

#The operating system is checked.
#Se verifica el sistema operativo.
ifeq ($(OS),Windows_NT)
    OS_detected := Windows
else
    OS_detected := $(shell uname -s)
endif

#Executable name.
#Nombre del ejecutable.
EXECUTABLE_NAME = mm1

#Select the variables to change depending on the OS.
#Se seleccionan las variables a cambiar dependiendo del SO. 

ifeq ($(OS_detected), Windows)
	EXTENSION = .exe
	EXECUTABLE = $(EXECUTABLE_NAME)$(EXTENSION)
	EXECUTE = $(EXECUTABLE)
    REMOVE = -del
	FILES = $(BUILD)\*.o

endif
ifeq ($(OS_detected), Linux)
	EXECUTABLE = $(EXECUTABLE_NAME)
	EXECUTE = ./$(EXECUTABLE)
    REMOVE = -rm -f
	FILES = $(BUILD)/*.o
endif

#Modules, headers and build folders.
#Carpeta de modulos, cabeceras y compilados.
HEADERS = include
SOURCES = src
BUILD = build

#Variables
CC = gcc -g
HDRS = -I $(HEADERS)/
BLDS = $(BUILD)/
FLAGS = -Wall -g3
EXTERNAL_LIBRARIES = -lm

SRCS = $(wildcard $(SOURCES)/*.c)
OBJS = $(subst $(SOURCES)/, $(BUILD)/,$(patsubst %.c,%.o,$(SRCS)))
MAIN = main
GLOBAL_DEPENDS = $(HEADERS)/structs.h $(HEADERS)/constants.h

.SILENT: all clean $(EXECUTABLE)
all: $(EXECUTABLE)

# Normal compilation
$(EXECUTABLE): $(OBJS) $(BUILD)/$(MAIN).o
	$(CC) -o $@ $^ $(EXTERNAL_LIBRARIES)
	@echo Compilation done. Executable: $(EXECUTE)

$(BUILD)/%.o: $(SOURCES)/%.c $(HEADERS)/%.h $(GLOBAL_DEPENDS) | $(BUILD)
	$(CC) $(FLAGS) $(HDRS) -c $< -o $@

$(BUILD)/$(MAIN).o: $(MAIN).c $(GLOBAL_DEPENDS)
	$(CC) $(FLAGS) $(HDRS) -c $(MAIN).c -o $(BUILD)/$(MAIN).o

$(BUILD):
	mkdir $@

# End normal compilation
clean:
	$(REMOVE) $(FILES)
	$(REMOVE) $(EXECUTABLE) debug_$(EXECUTABLE)
	@echo Full wipe.

.PHONY: clean


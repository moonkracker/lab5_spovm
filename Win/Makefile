CC = gcc
CFLAGS = -c -Wall -pedantic
SHAREDFLAG = -shared
STAND:=  -std=c99
APP = lab5
LIB = library.dll
APP_SOURCES = main.c functions.c
APP_OBJECTS = $(APP_SOURCES:.c=.o)
LIB_SOURCES = library.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)

all: $(LIB) $(APP) clean run

$(LIB): $(LIB_OBJECTS)
	$(CC) $(LIB_OBJECTS) $(SHAREDFLAG) $(STAND) -o $@

$(APP): $(APP_OBJECTS)
	$(CC) $(APP_OBJECTS) $(STAND) -o $@

.c.o:
	$(CC) $(CFLAGS) $(STAND) $< -o $@

.PHONY: clean
clean:
	del $(APP_OBJECTS) $(LIB_OBJECTS)
run:
	$(APP)
	code Files/OUTPUT


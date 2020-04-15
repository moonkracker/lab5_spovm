CC = gcc
CFLAGS = -c -Wall -pedantic -fPIC -D_XOPEN_SOURCE=600
SHAREDFLAG = -shared
THREADFLAG = -pthread
AIOFLAG = -lrt
LIBFLAG = -ldl
STAND:=  -std=c99
APP = lab5
LIB = library.so
APP_SOURCES = main.c func.c
APP_OBJECTS = $(APP_SOURCES:.c=.o)
LIB_SOURCES = library.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)

all: $(LIB) $(APP) clean run

$(LIB): $(LIB_OBJECTS)
	$(CC) $(LIB_OBJECTS) $(SHAREDFLAG) $(STAND) -o $@ $(AIOFLAG)

$(APP): $(APP_OBJECTS)
	$(CC) $(THREADFLAG) $(APP_OBJECTS) $(STAND) -o $@ $(LIBFLAG)

.c.o:
	$(CC) $(THREADFLAG) $(CFLAGS) $(STAND) $< -o $@ $(AIOFLAG) $(LIBFLAG)

.PHONY: clean
clean:
	rm -rf $(APP_OBJECTS) $(LIB_OBJECTS)

run:
	./$(APP)
	code Files/OUTPUT
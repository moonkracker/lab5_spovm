#ifndef HEADER_H
#define HEADER_H

#define BUFFER_SIZE 512
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <process.h>
#include <locale.h>
#include <string.h>

struct Info
{
	HANDLE mutex;
	HANDLE readThread, writeThread;
	HINSTANCE library;
	char buffer[512];
	volatile int flag;
	char **fileNames;
	int threadsNumber;
};

DWORD WINAPI threadReader(LPVOID t);
DWORD WINAPI threadWriter(LPVOID t);

typedef void (*ReadDataFromFile)(HANDLE, char*);
typedef void (*WriteDataInFile)(HANDLE, char*);

void initInfo(struct Info *);
void createMutex(struct Info *);
void runThreads(struct Info *);
void waitThreads(struct Info *);

#endif
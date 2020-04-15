#include "header.h"

#define FILES_COUNT 5

char *files[FILES_COUNT] = { "Files\\1", "Files\\2", "Files\\3", "Files\\4", "Files\\5"};                                              //Каталог файлов

DWORD WINAPI threadReader(LPVOID t)
{
	struct Info *info = (struct Info *)t;                                                                                   //Приведение к типу аргумента функции
	ReadDataFromFile readDataFromFile = (ReadDataFromFile) GetProcAddress(info->library,"ReadDataFromFile");				//Установка указателя на функцию из библиотеки

	for(int i = 0; i < FILES_COUNT; i++)
	{
		while(info->flag) {};																							    //Ожидаем флаг
		WaitForSingleObject(info->mutex, INFINITE);																		    //Захват мьютекса
		HANDLE hFile = CreateFile(info->fileNames[i], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);    //Открываем существующий файл для чтения
		(*readDataFromFile)(hFile, info->buffer);                                                                           //Читаем файл функцией из библиотеки
		CloseHandle(hFile);																									//Закрываем файл
		info->flag = 1;																										//Устанавливаем флаг
		ReleaseMutex(info->mutex);																						    //Отпускаем мьютекс
	}
	info->threadsNumber--;
	return 0;
}

DWORD WINAPI threadWriter(LPVOID t)
{
	struct Info *info = (struct Info *)t;
	WaitForSingleObject(info->mutex, INFINITE);
	HANDLE hFile = CreateFile("Files\\OUTPUT", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);          //Открываем файл для записи
	WriteDataInFile writeDataInFile = (WriteDataInFile) GetProcAddress(info->library,"WriteDataInFile");					//Указатель на функцию записи
	ReleaseMutex(info->mutex);

	for(int i = 0; i < FILES_COUNT; i++)
	{
		while(!info->flag) {};
		WaitForSingleObject(info->mutex, INFINITE);
		(*writeDataInFile)(hFile, info->buffer);
		ReleaseMutex(info->mutex);
		info->flag = 0;
	}
	CloseHandle(hFile);
	info->threadsNumber--;
	return 0;
}

void initInfo(struct Info *info)
{
	info->fileNames = files;
	if(!(info->library = LoadLibrary("library.dll")))                                                                          //Открываем библиотеку
	{
		printf("library.dll is not found\n");
		exit(-3);
	}
	info->threadsNumber = 0;
	info->flag = 0;

}

void createMutex(struct Info *info)
{
	info->mutex =  CreateMutex(NULL, FALSE, NULL);
}

void runThreads(struct Info *info)
{
	info->readThread = CreateThread(NULL, 0, threadReader, (void *)info, 0, NULL);                                           //создаем поток чтения
	info->threadsNumber++;
	info->writeThread = CreateThread(NULL, 0, threadWriter, (void *)info, 0, NULL);										     //поток записи
	info->threadsNumber++;	
}

void waitThreads(struct Info *info)
{
	while(info->threadsNumber);
	CloseHandle(info->readThread);
	CloseHandle(info->writeThread);
	CloseHandle(info->mutex);
	FreeLibrary(info->library);
	printf("OK\n");
}
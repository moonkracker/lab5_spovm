#include <windows.h>

#define BUFFER_SIZE 512

void WriteDataInFile(HANDLE hFile, char* buff)
{
	struct _OVERLAPPED overlapped;                                        //Указатель на структуру overlapped
	overlapped.Offset = 0xFFFFFFFF;										  //Местоположение файла, в котором начинается передача
	overlapped.OffsetHigh = 0xFFFFFFFF;									  //Старшее слово позиции файла, в который начинается передача
	overlapped.hEvent = NULL;											  //Дескриптор события, которые должно быть установлено в сигнальное состояние, когда операция завершилась
	DWORD cbWritten;												      //Число записанных байт										  
	WriteFile(hFile,                                                      //Дескриптор файла
			  buff,                                                       //Буфер данных
			  strlen(buff), 											  //Число байт для записи
			  &cbWritten, 												  //Число записанных байт
			  &overlapped);                                               //Асинхроннный буфер
	WaitForSingleObject(hFile, INFINITE);								  //Ожидание файлового дескриптора
}

void ReadDataFromFile(HANDLE hFile, char* buff)
{
	memset(buff, 0, BUFFER_SIZE * sizeof(char));                          //Выделение памяти под буфер
	struct _OVERLAPPED overlapped;
	overlapped.Offset = 0; 												  //Местоположение файла, в котором начинается передача
	overlapped.OffsetHigh = 0;
	overlapped.hEvent = NULL;
	DWORD cbRead;
	ReadFile(hFile, 													  //Дескриптор файла
			 buff,                                                        //Буфер данных
			 BUFFER_SIZE, 												  //Число байт для чтения
			 &cbRead, 													  //Число прочитанных байт
			 &overlapped);												  //Асинхронный буфер
}
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <aio.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 512

void readFromFile(int fd, char *buffer)                  //Чтение данных файла
{
	memset(buffer,										 //Указатель на блок памяти для заполнения.
		   0, 											 //Функция заполняет блок памяти символом, преобразуя это число в символ.
		   SIZE * sizeof(char));                         //Количество байт для заполнения 
	struct aiocb aioInfo;                                //Указатель на структуру aiocb
	memset(&aioInfo, 0, sizeof(struct aiocb));           //Выделение памяти под структуру
	aioInfo.aio_fildes = fd;						     //Файловый дескриптор
	aioInfo.aio_buf = buffer;							 //Расположение буфера
	aioInfo.aio_nbytes = SIZE;						     //Длина передачи 
	aioInfo.aio_lio_opcode = LIO_READ;				     //Выполняемая операция (чтение)
	if(aio_read(&aioInfo) == -1)                         //Асинхронное чтение
	{
		printf("Error at aio_read\n");					
		close(fd);
		exit(EXIT_FAILURE);							     //Выход если ошибка
	}
	while(aio_error(&aioInfo) == EINPROGRESS);			 //Ожидание завершения работы
}


void writeToFile(int fd, char *buffer)
{
	struct aiocb aioInfo;
	memset(&aioInfo, 0, sizeof(struct aiocb));
	aioInfo.aio_fildes = fd;
	aioInfo.aio_buf = buffer;
	aioInfo.aio_nbytes = strlen(buffer);
	aioInfo.aio_lio_opcode = LIO_WRITE;                   //Операция записи
	if(aio_write(&aioInfo) == -1)
	{
		printf("Error at aio_write\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	while(aio_error(&aioInfo) == EINPROGRESS);
}
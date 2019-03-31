#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, write_block;
int data = 0, read_count = 0;

void *reader(void *arg)
{
	int f;
	f = ((int)arg);
	sem_wait(&mutex);
	read_count = read_count + 1;
	if (read_count == 1)
		sem_wait(&write_block);
	sem_post(&mutex);
	printf("Reader %d reads %d\n", f, data);
	sleep(1);
	sem_wait(&mutex);
	read_count = read_count - 1;
	if (read_count == 0)
		sem_post(&write_block);
	sem_post(&mutex);
}

void *writer(void *arg)
{
	int f;
	f = ((int)arg);
	sem_wait(&write_block);
	data++;
	printf("Writer %d writes %d\n", f, data);
	sleep(1);
	sem_post(&write_block);
}

void main()
{

    printf("\n------------------------------------------------------------------------------------------\n");
    printf("                           SOLUTION TO READER-WRITER PROBLEM                                \n");
    printf("------------------------------------------------------------------------------------------\n\n");
    sleep(1);
	int i, b;
	pthread_t rtid[5], wtid[5];
	sem_init(&mutex, 0, 1);
	sem_init(&write_block, 0, 1);
	for (i = 0; i <= 2; i++)
	{
		pthread_create(&wtid[i], NULL, writer, (void *)i);
		pthread_create(&rtid[i], NULL, reader, (void *)i);
	}
	for (i = 0; i <= 2; i++)
	{
		pthread_join(wtid[i], NULL);
		pthread_join(rtid[i], NULL);
	}
}
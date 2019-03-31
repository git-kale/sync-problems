#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

sem_t agent_ready;

sem_t smoker_semaphors[3];
char* smoker_types[3] = { "matches & tobacco", "matches & paper", "tobacco & paper" };

bool items_on_table[3] = { false, false, false };

sem_t pusher_semaphores[3];

void* smoker(void* arg)
{
	int smoker_id = *(int*) arg;
	int type_id   = smoker_id % 3;

	for (int i = 0; i < 3; ++i)
	{
		printf("Smoker %d Waiting for %s\n",
			smoker_id, smoker_types[type_id]);

		sem_wait(&smoker_semaphors[type_id]);

		printf("Smoker %d Now making the a cigarette\n", smoker_id);
		usleep(rand() % 50000);
		sem_post(&agent_ready);

		printf("Smoker %d Now smoking\n", smoker_id);
		usleep(rand() % 50000);
	}

	return NULL;
}

sem_t pusher_lock;

void* pusher(void* arg)
{
	int pusher_id = *(int*) arg;

	for (int i = 0; i < 12; ++i)
	{
		sem_wait(&pusher_semaphores[pusher_id]);
		sem_wait(&pusher_lock);

		if (items_on_table[(pusher_id + 1) % 3])
		{
			items_on_table[(pusher_id + 1) % 3] = false;
			sem_post(&smoker_semaphors[(pusher_id + 2) % 3]);
		}
		else if (items_on_table[(pusher_id + 2) % 3])
		{
			items_on_table[(pusher_id + 2) % 3] = false;
			sem_post(&smoker_semaphors[(pusher_id + 1) % 3]);
		}
		else
		{
			items_on_table[pusher_id] = true;
		}

		sem_post(&pusher_lock);
	}

	return NULL;
}

void* agent(void* arg)
{
	int agent_id = *(int*) arg;

	for (int i = 0; i < 6; ++i)
	{
		usleep(rand() % 200000);
		sem_wait(&agent_ready);

		sem_post(&pusher_semaphores[agent_id]);
		sem_post(&pusher_semaphores[(agent_id + 1) % 3]);
    
		printf("\n=====>  Agent %d giving out %s  <========\n\n",
			agent_id, smoker_types[(agent_id + 2) % 3]);
	}

	return NULL;
}

int main(int argc, char* arvg[])
{

    printf("\n------------------------------------------------------------------------------------------\n");
    printf("                              SOLUTION TO CIGGARATE SMOKERS                                 \n");
    printf("------------------------------------------------------------------------------------------\n\n");
    sleep(1);

	srand(time(NULL));

	sem_init(&agent_ready, 0, 1);

	sem_init(&pusher_lock, 0, 1);

	for (int i = 0; i < 3; ++i)
	{
		sem_init(&smoker_semaphors[i], 0, 0);
		sem_init(&pusher_semaphores[i], 0, 0);
	}

	int smoker_ids[6];

	pthread_t smoker_threads[6];
	for (int i = 0; i < 6; ++i)
	{
		smoker_ids[i] = i;

		if (pthread_create(&smoker_threads[i], NULL, smoker, &smoker_ids[i]) == EAGAIN)
		{
			perror("Insufficient resources to create thread");
			return 0;
		}
	}

	int pusher_ids[6];

	pthread_t pusher_threads[6];

	for (int i = 0; i < 3; ++i)
	{
		pusher_ids[i] = i;

		if (pthread_create(&pusher_threads[i], NULL, pusher, &pusher_ids[i]) == EAGAIN)
		{
			perror("Insufficient resources to create thread");
			return 0;
		}
	}

	int agent_ids[6];

	pthread_t agent_threads[6];

	for (int i = 0; i < 3; ++i)
	{
		agent_ids[i] =i;

		if (pthread_create(&agent_threads[i], NULL, agent, &agent_ids[i]) == EAGAIN)
		{
			perror("Insufficient resources to create thread");
			return 0;
		}
	}
	for (int i = 0; i < 6; ++i)
	{
		pthread_join(smoker_threads[i], NULL);
	}

}
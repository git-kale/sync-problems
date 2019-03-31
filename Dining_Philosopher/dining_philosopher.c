#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N           5
#define EATING      0
#define HUNGRY      1
#define THINKING    2
#define TRUE        1
#define LEFT        ((i + N - 1) % N)
#define RIGHT       ((i + 1) % N)

int state[N];
int philosopher_number[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[N];

void test(i)
	int i;
{
	if (state[i] == HUNGRY &&
	state[LEFT] != EATING &&
	state[RIGHT] != EATING)
	{
		state[i] = EATING;

		sleep(1);
		printf("Philosopher %d takes fork %d and %d\n",
			i + 1,
			LEFT + 1,
			i + 1
		);
		printf("Philosopher %d is Eating\n", i + 1);
		sem_post(&S[i]);
	}
}

void take_fork(i)
	int i;
{
	sem_wait(&mutex);

	state[i] = HUNGRY;

	printf("Philosopher %d is Hungry\n", i + 1);
	test(i);
	sem_post(&mutex);
	sem_wait(&S[i]);
	sleep(1);
}

void put_fork(i)
	int i;
{
	sem_wait(&mutex);

	state[i] = THINKING;

	printf("Philosopher %d putting fork %d and %d down\n",
		i + 1,
		LEFT + 1,
		i + 1
	);
	printf("Philosopher %d is thinking\n", i + 1);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}

void *philosopher(num)
	void *num;
{
	while (TRUE) {
		int *i = (int *) num;

		sleep(1);
		take_fork(*i);
		put_fork(*i);
	}
}

int main(void)
{

    printf("\n------------------------------------------------------------------------------------------\n");
    printf("                           SOLUTION TO SLEEPING BARBER PROBLEM                              \n");
    printf("------------------------------------------------------------------------------------------\n\n");
	sleep(1);
	pthread_t thread_id[N];

	sem_init(&mutex, 0, 1);

	for (int i = 0; i < N; ++i) {
		sem_init(&S[i], 0, 0);
	}
	for (int i = 0; i < N; ++i) {
		pthread_create(
			&thread_id[i],
			NULL,
			philosopher,
			&philosopher_number[i]
		);
		printf("Philosopher %d is thinking\n", i + 1);
	}
	for (int i = 0; i < N; ++i) {
		pthread_join(thread_id[i], NULL);
	}
}
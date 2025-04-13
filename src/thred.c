#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 5

void *philosopher(void *arg)
{
	int fd = *(int *)arg;
	printf("Philosopher %d is thinking...\n", fd);
	sleep(1);
	printf("Philosopher %d is done...\n", fd);
	return NULL;
}

int main()
{
	pthread_t threads[NUM_THREADS];
	int ids[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++) {
		ids[i] = i + 1;
		pthread_create(&threads[i], NULL, philosopher, &ids[i]);
	}

	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}
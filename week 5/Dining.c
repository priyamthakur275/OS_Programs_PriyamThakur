#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

enum { THINKING, HUNGRY, EATING } state[N];
pthread_mutex_t mutex;
sem_t sem[N];  // One semaphore per philosopher

void test(int i) {
    if (state[i] == HUNGRY &&
        state[(i + 4) % N] != EATING &&
        state[(i + 1) % N] != EATING) {
        state[i] = EATING;
        sem_post(&sem[i]);
    }
}

void take_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", i);
    test(i);
    pthread_mutex_unlock(&mutex);
    sem_wait(&sem[i]);
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d puts down forks and starts THINKING\n", i);
    test((i + 4) % N);  // Test left neighbor
    test((i + 1) % N);  // Test right neighbor
    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num) {
    int i = *(int*)num;
    while (1) {
        printf("Philosopher %d is THINKING\n", i);
        sleep(1);
        take_forks(i);
        printf("Philosopher %d is EATING\n", i);
        sleep(2);
        put_forks(i);
    }
}

int main() {
    pthread_t tid[N];
    int i, phil[N];

    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++) {
        sem_init(&sem[i], 0, 0);
        state[i] = THINKING;
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

/* output :
Philosopher 0 is THINKING
Philosopher 1 is THINKING
Philosopher 0 is HUNGRY
Philosopher 0 is EATING
Philosopher 2 is THINKING
...
Philosopher 0 puts down forks and starts THINKING
...
*/

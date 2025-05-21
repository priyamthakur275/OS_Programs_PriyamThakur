#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE 5

int buffer[MAX_BUFFER_SIZE];
int count = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; 
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); 
        buffer[count] = item;
        count++;
        printf("Produced: %d\n", item);
        pthread_mutex_unlock(&mutex); 
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full); 
        pthread_mutex_lock(&mutex);
        item = buffer[count - 1]; 
        count--;
        printf("Consumed: %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); 
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    
    sem_init(&empty, 0, MAX_BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL); 

    
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

   
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

/*
Output:

Produced: 73
Consumed: 73
Produced: 41
Consumed: 41
Produced: 56
Consumed: 56
Produced: 18
Consumed: 18
Produced: 99
Consumed: 99
Produced: 55
Consumed: 55
Produced: 63
Consumed: 63
Produced: 84
Consumed: 84
...
  */

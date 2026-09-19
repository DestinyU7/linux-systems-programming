#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define parameter data structure
struct data {
    int thread_id;
    int total_threads;
};

// Define mutex data structure
pthread_mutex_t mut;

void* print(void *ptr){
    struct data *d = (struct data *)ptr; // Cast the pointer to the correct type
    pthread_mutex_lock(&mut);
    printf("I am thread %d in %d\n", d->thread_id, d->total_threads); // Print thread information
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main (int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: %s <nbthreads>\n", argv[0]);
        return -1;
    }
    
    int n_thread = atoi(argv[1]);
    pthread_mutex_init(&mut, NULL);
    
    pthread_t* threads = (pthread_t*) malloc (sizeof(pthread_t) * n_thread);
    struct data d[n_thread];
    
    for (int i = 0; i < n_thread; i++){
        d[i].thread_id = i; // Assign thread ID
        d[i].total_threads = n_thread; // Assign total number of threads
        if (pthread_create(&threads[i], NULL, print, (void*)&d[i]) != 0) {
            perror("Failed to create thread");
            free(threads);
            return -1;
        }
    }
    
    for (int i = 0; i < n_thread; i++){
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    
    free(threads); // Free allocated memory for threads
    pthread_mutex_destroy(&mut); // Destroy the mutex
    
    return 0;
}
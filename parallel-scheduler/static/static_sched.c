#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Define the ProgramInput struct
struct ProgramInput {
    int function_id;
    float a;
    float b;
    int n;
    int intensity;
    int num_threads;
    const char* sync;
};

// Function prototypes
void* thread_function(void* arg);
float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x);
float f4(float x, int intensity);

// Mutex for thread-level mutual exclusion
pthread_mutex_t mut;

// Global result
float global_result = 0.0;

// Structure to hold parameters for each thread
struct Params {
    int start_index;
    int end_index;
    float a;
    float ban;
    int intensity;
    int function_id;
    const char* sync;
    float* result;
};

// Function to perform numerical integration
float pthread_numerical_integration(int argc, char* argv[]) {
    // Get command line inputs
    struct ProgramInput prog_in;
    prog_in.function_id = atoi(argv[1]);
    prog_in.a = atof(argv[2]);
    prog_in.b = atof(argv[3]);
    prog_in.n = atoi(argv[4]);
    prog_in.intensity = atoi(argv[5]);
    prog_in.num_threads = atoi(argv[6]);
    prog_in.sync = argv[7];

    // Initialize global result
    global_result = 0.0;

    // Initialize mutex
    pthread_mutex_init(&mut, NULL);
    pthread_t threads[prog_in.num_threads];

    // Declare params and fill them
    struct Params params[prog_in.num_threads];
    float ban = (prog_in.b - prog_in.a) / prog_in.n;
    int chunk = prog_in.n / prog_in.num_threads;

    for (int i = 0; i < prog_in.num_threads; i++) {
        params[i].start_index = i * chunk;
        params[i].end_index = MIN(prog_in.n - 1, (i + 1) * chunk - 1);
        params[i].a = prog_in.a;
        params[i].ban = ban;
        params[i].intensity = prog_in.intensity;
        params[i].function_id = prog_in.function_id;
        params[i].sync = prog_in.sync;
        params[i].result = &global_result;
    }

    // Create threads
    for (int i = 0; i < prog_in.num_threads; i++) {
        pthread_create(&threads[i], NULL, thread_function, &params[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < prog_in.num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mut);

    // Return the computed result
    return global_result;
}

// Thread function implementation
void* thread_function(void* arg) {
    struct Params* params = (struct Params*) arg;
    float local_result = 0.0;
    for (int i = params->start_index; i <= params->end_index; i++) {
        float x = params->a + (i + 0.5) * params->ban;
        float value;
        switch (params->function_id) {
            case 1:
                value = f1(x, params->intensity);
                break;
            case 2:
                value = f2(x, params->intensity);
                break;
            case 3:
                value = f3(x);
                break;
            case 4:
                value = f4(x, params->intensity);
                break;
            default:
                value = 0.0;
                break;
        }
        local_result += value * params->ban;
    }
    if (strcmp(params->sync, "iteration") == 0) {
        pthread_mutex_lock(&mut);
        *params->result += local_result;
        pthread_mutex_unlock(&mut);
    } else if (strcmp(params->sync, "thread") == 0) {
        pthread_mutex_lock(&mut);
        *params->result += local_result;
        pthread_mutex_unlock(&mut);
    }
    return NULL;
}

// Function implementations
float f1(float x, int intensity) {
    float result = x;
    for (int i = 0; i < intensity; i++) {
        result = result * result;
        result = sqrt(result);
    }
    return result;
}

float f2(float x, int intensity) {
    float result = x * x;
    for (int i = 0; i < intensity; i++) {
        result = result * result;
        result = sqrt(result);
    }
    return result;
}

float f3(float x) {
    return sin(x);
}

float f4(float x, int intensity) {
    float result = exp(cos(x));
    for (int i = 0; i < intensity; i++) {
        result = result * result;
        result = sqrt(result);
    }
    return result;
}

// Main function
int main(int argc, char* argv[]) {
    if (argc < 8) {
        printf("usage: %s <functionid> <a> <b> <n> <intensity> <nbthreads> <sync>\n", argv[0]);
        return -1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    float result = pthread_numerical_integration(argc, argv);

    gettimeofday(&end, NULL);

    fprintf(stdout, "%f\n", result);
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed_seconds = seconds + microseconds / 1000000.0;

    fprintf(stderr, "%f\n", elapsed_seconds);

    return 0;
}



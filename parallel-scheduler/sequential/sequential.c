#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

float f1(float x, int intensity) {
    int sign = x > 0;

    for (int i = 0; i < intensity; ++i) {
        x = x * x;
        x = sqrt(x);
    }
    return (sign ? 1 : -1) * x;
}

float f2(float x, int intensity) {
    float realx = f1(x, intensity);
    return realx * realx;
}

float f3(float x, int intensity) {
    return sin(f1(x, intensity));
}

float f4(float x, int intensity) {
    return exp(cos(f1(x, intensity)));
}

float sequential_integrate(int argc, char* argv[]) {
    int functionid = atoi(argv[1]);
    float a = atof(argv[2]);
    float b = atof(argv[3]);
    int n = atoi(argv[4]);
    int intensity = atoi(argv[5]);

    float (*f)(float, int) = NULL;

    if (functionid == 1) {
        f = f1;
    } else if (functionid == 2) {
        f = f2;
    } else if (functionid == 3) {
        f = f3;
    } else if (functionid == 4) {
        f = f4;
    }

    if (f == NULL) {
        fprintf(stderr, "Invalid function ID: %d\n", functionid);
        return -1;
    }

    double sum = 0;

    for (int i = 0; i < n; ++i) {
        float x = a + (i + .5) * (b - a) / n;
        float val = f(x, intensity);
        sum += val;
    }
    float integrate = sum * (b - a) / n;

    return integrate;
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        printf("usage: %s <functionid> <a> <b> <n> <intensity>\n", argv[0]);
        return -1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    float integrate = sequential_integrate(argc, argv);

    gettimeofday(&end, NULL);

    fprintf(stdout, "%f\n", integrate);
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed_seconds = seconds + microseconds / 1000000.0;

    fprintf(stderr, "%f\n", elapsed_seconds);

    return 0;
}

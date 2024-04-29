#define _GNU_SOURCE
#define CPU_ZERO
#define CPU_SET
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>
#include <time.h>


int main(int argc, char **argv) {

    // Set CPU affinity
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);

    int pagesToTouch = 1024;
    int numberOfTrials = 1000000;

    int parameter;

    // Parse command line arguments
    while ((parameter = getopt(argc, argv, "p:n:")) != -1) {
        switch (parameter) {
            case 'p':
                pagesToTouch = atoi(optarg);
                break;
            case 'n':
                numberOfTrials = atoi(optarg);
                break;
            default:
                printf("Usage: %s -p <pagesToTouch> -n <numberOfTrials>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Error checking
    if (pagesToTouch <= 0 || numberOfTrials <= 0) {
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }

    printf("%d,",pagesToTouch);

    // Get page size
    int pageSize = getpagesize();
    int jump = pageSize / sizeof(int);
    int *a = (int *) calloc(pagesToTouch, pageSize);

    if (a == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    struct timespec start, end;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < numberOfTrials; i++) {
        for (int j = 0; j < pagesToTouch * jump; j += jump) {
            a[j] += 1;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%lf\n", (end.tv_sec * 1e9 + end.tv_nsec - start.tv_sec * 1e9 + start.tv_nsec) / (double) numberOfTrials);
    free(a);
    return 0;
}
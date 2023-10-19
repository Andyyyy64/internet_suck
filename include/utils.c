#include "utils.h"
#include <time.h>

static clock_t start_time;

void start_timer() {
    start_time = clock();
}

double end_timer() {
    return (double)(clock() - start_time) / CLOCKS_PER_SEC;
}
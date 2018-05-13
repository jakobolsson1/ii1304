#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

enum {
    STEADY,
    TRANSIENT,
    __METHOD_MAX
};

static char *method_type[__METHOD_MAX] = {"steady", "transient"};

int parse_args(int argc, char **argv, int *method, int *values, int *enqueues);

#include "common.h"

struct option longopts[] = {
    { "steady",      no_argument,            NULL,           's' },
    { "values",   required_argument,      NULL,           'v' },
    { "transient",  no_argument,            NULL,     't' },
    { "enqueues",  required_argument,            NULL,     'e' }

};

int parse_args(int argc, char **argv, int *method, int *values, int *enqueues)
{
    int ch;

    while ((ch = getopt_long(argc, argv, "bf:", longopts, NULL)) != -1)
        switch (ch) {
        case 's':
            *method = STEADY;
            break;
        case 'v':
            *values = atoi(optarg);
            break;
        case 't':
            *method = TRANSIENT;
            break;
        case 'e':
            *enqueues = atoi(optarg);
            break;
        default:
            goto fail;
            break;
    }
    
    if(*method == STEADY) {
        if(!(*values && *enqueues))
            goto fail;
    } else {
        if(!(*values))
            goto fail;
    }

    printf("method: %d, values %d", *method, *values);
    if (*enqueues)
        printf(" enqueues %d", *enqueues);
    printf("\n");
     return 0;
fail:
     return -1;
}

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "cli_options.h"
#include "version.h"

void parse_command_options(int argc, char *const argv[],
                           command_t command_queue[], int parameter_queue[])
{
    struct option long_options[] =
    {
        {"version",  no_argument,       NULL, 'v'},
        {"flip",     required_argument, NULL, 'F'},
        {"gray",     no_argument,       NULL, 'G'},
        {"quantize", required_argument, NULL, 'Q'},
        {0}
    };

    int option, queue_ind = -1;
    opterr = 0;
    while ((option = getopt_long(argc, argv, "vF:GQ:", long_options, NULL)) != -1) {
        if (queue_ind++ < 15) {
            switch (option) {
                case 'v':
                    printf("fotoxope CLI v" FOTOXOPE_CLI_VERSION_STRING "\n");
                    exit(EXIT_SUCCESS);
                    break;
                case 'F':
                    command_queue[queue_ind] = optarg[0] == 'h' ? FLIP_H : FLIP_V;
                    if (optarg[0] != 'h' && optarg[0] != 'v') {
                        fprintf(stderr, "Error: flip parameter unknown: '%s' (must be horizontal|vertical) \n", optarg);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'G':
                    command_queue[queue_ind] = GRAY;
                    break;
                case 'Q':
                    command_queue[queue_ind] = QUANTIZE;
                    parameter_queue[queue_ind] = atoi(optarg);
                    if (parameter_queue[queue_ind] == 0) {
                        fprintf(stderr, "Error: quantization parameter unknown: '%s' (must be 2-128) \n", optarg);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case '?':
                    if (optopt == 'F' || optopt == 'Q')
                        fprintf (stderr, "Error: option '-%c' requires an argument \n", optopt);
                    else
                        fprintf (stderr, "Error: unknown option '-%c' \n", optopt);
                default:
                    exit(EXIT_FAILURE);
            }
        } else if (queue_ind == 16) {
            fprintf(stderr, "Error: maximum of 16 chained commands reached \n");
        }
    }
}

void parse_IO_options(int argc, char *const argv[],
                      char **in, char **out)
{
    *in = *out = NULL;

    switch (argc - optind) {
        case 2:
            *in = argv[optind++];
            *out = argv[optind];
            break;
        case 1:
            *out = *in = argv[optind];
            break;
        default:
            fprintf (stderr, "Error: no image file given");
            exit(EXIT_FAILURE);
    }
}

void parse_options(int argc, char *const argv[],
                   command_t *command, int *parameter,
                   char **in, char **out)
{
    parse_command_options(argc, argv, command, parameter);
    parse_IO_options(argc, argv, in, out);
}

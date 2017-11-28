#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "cli_options.h"
#include "version.h"

void parse_command_options(int argc, char *const argv[],
                           command_t *command, int *parameter)
{
    struct option long_options[] =
    {
        {"version",  no_argument,       NULL, 'v'},
        {"flip",     required_argument, NULL, 'F'},
        {"gray",     no_argument,       NULL, 'G'},
        {"quantize", required_argument, NULL, 'Q'},
        {0}
    };

    *command = NOTHING;

    int option;
    opterr = 0;
    while ((option = getopt_long(argc, argv, "vF:GQ:", long_options, NULL)) != -1) {
        switch (option) {
            case 'v':
                printf("fotoxope CLI v" FOTOXOPE_CLI_VERSION_STRING "\n");
                exit(EXIT_SUCCESS);
                break;
            case 'F':
                *command = optarg[0] == 'h' ? FLIP_H : FLIP_V;
                if (optarg[0] != 'h' && optarg[0] != 'v') {
                    fprintf(stderr, "Error: flip parameter unknown: '%s' (must be horizontal|vertical) \n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'G':
                *command = GRAY;
                break;
            case 'Q':
                *command = QUANTIZE;
                *parameter = atoi(optarg);
                if (*parameter == 0) {
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

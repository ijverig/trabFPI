// FOTOXOPE_CLI_VERSION
#define V_MAJOR 1
#define V_MINOR 0
#define V_PATCH 0

#define FOTOXOPE_CLI_VERSION_STRING TO_STRING(FOTOXOPE_CLI_VERSION)

/* ================================================================= */

#if V_PATCH == 0
    #define FOTOXOPE_CLI_VERSION V_MAJOR.V_MINOR
#else
    #define FOTOXOPE_CLI_VERSION V_MAJOR.V_MINOR.V_PATCH
#endif

#define STRING(s) #s
#define TO_STRING(s) STRING(s)

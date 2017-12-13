#include "session.h"

enum MENU_OPTION
{
    OPTION_NOTHING,

    OPTION_OPEN,
    OPTION_SAVE,

    OPTION_HISTOGRAM,
    
    OPTION_FLIP_H,
    OPTION_FLIP_V,

    OPTION_GRAYSCALE,
    OPTION_QUANTIZE,

    OPTION_EXIT,
};

void interaction_init();

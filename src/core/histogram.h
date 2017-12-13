#include "image.h"

void histogram_compute(int histogram[256], image_t *image);
int histogram_max_value(int histogram[256]);
void histogram_normalize(int histogram[256]);

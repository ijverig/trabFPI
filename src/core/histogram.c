#include "histogram.h"
#include <syslog.h>

void histogram_compute(int histogram[256], image_t *image)
{
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    for (int i = 0; i < image->width * image->height * image->depth; i += 3) {
        ++histogram[image->data[i]];
    }
}

int histogram_max_value(int histogram[256])
{
    int max_value = histogram[0];
    for (int i = 1; i < 256; i++)
    {
        if (histogram[i] > max_value) {
            max_value = histogram[i];
        }
    }

    return max_value;
}

void histogram_normalize(int histogram[256])
{
    int max_value = histogram_max_value(histogram);
    for (int i = 0; i < 256; i++) {
        histogram[i] = 255 * histogram[i] / (1.05 * max_value);
    }
}

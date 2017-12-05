#ifndef IMAGE_HEADER
#define IMAGE_HEADER

// alias to list of [width][depth] arrays (scanlines)
#define DATA_AS_3D_MATRIX(m, i, d) byte (*m)[i->width][i->depth] = (byte (*)[i->width][i->depth]) (d)
#define IMAGE_DATA_AS_3D_MATRIX(m, i) DATA_AS_3D_MATRIX(m, i, i->data)

typedef unsigned char byte;
typedef struct image image_t;

enum PIXEL_CHANNEL
{
  // GrayPixelChannel = 0,
  R = 0,
  G = 1,
  B = 2,
  // AlphaPixelChannel = 3,
};

struct image
{
    int width, height, depth, size;
    byte *data;
};

void image_flip_vertically_on_load();
void image_save(image_t image, const char *filename);
image_t image_create_from_file(const char *filename);
image_t image_create_from_image(image_t image);
void image_destroy(image_t image);

#include "transformations.h"
#include "filters.h"

#endif

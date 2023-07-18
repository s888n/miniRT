#include "rt.h"

int clamp(double c)
{
    int clr = (int)(c * 255.999);
    if(clr > 255)
        clr = 255;
    if(clr < 0)
        clr = 0;
    return clr;
}

int rgb_to_int(t_v3 *color)
{
    int c = 0;

    c |= clamp(color->x) << 16;
    c |= clamp(color->y) << 8;
    c |= clamp(color->z);
    return c;
}

void put_pixel(t_image *image, int x, int y, int color)
{
    char *dst;
    dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
    *(int *)dst = color;
}
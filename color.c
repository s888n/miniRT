#include "rt.h"
void put_pixel(t_image *image, int x, int y, int color);
int rgb_to_int(t_color2 *color);
int normalize_color(double c)
{
    int clr = (int)(c * 256);
    if(clr > 255)
        clr = 255;
    return clr;
}

int rgb_to_int(t_color2 *color)
{
    int c = 0;

    c |= normalize_color(color->red) << 16;
    c |= normalize_color(color->green) << 8;
    c |= normalize_color(color->blue);
    return c;
}

void put_pixel(t_image *image, int x, int y, int color)
{
    char *dst;

    dst = (char *)image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
#include "rt.h"

/*this function stores a color in a screen pixel*/
/*image->addr is the address of the first pixel of the image*/
void put_pixel(t_image *image, int x, int y, int color)
{
    char *dst;

    dst = (char *)image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

/*here we use pixel_put to assign each pixel of the screen a color based on lighting ,camera,ambient light*/
// void drawScene()
// {
//     int i ,j;
//     i = H;
//     j =-1;
//     while (--i >= 0)
//         while (++j < W)
//             draw();//use put_pixel in draw()
 
    

// }

// void render()
// {
//     drawScene();
//     mlx_put_image_to_window();

// }
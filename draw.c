#include "rt.h"
int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
void draw(t_scene *scene)
{
    int i;
    int j;
    double u;
    double v;
    t_v3 color;
    t_ray r;

    j =0;
    color =(t_v3){scene->ambient_color.red *  scene->ambient_intensity, scene->ambient_color.green * scene->ambient_intensity, scene->ambient_color.blue * scene->ambient_intensity};
    while (j < H)
    {
        i = 0;
        while (i < W)
        {
            v = ((i + 0.5) * 2) / (W - 1);
            u = ((j + 0.5) * 2) / (H - 1);
            r = calculateRay(scene->camera, v, u);
            put_pixel(scene->image, i, j,rgb_to_int(&color));
            i++;
        }
        j++;
    }
}
#include "rt.h"
int create_rgb(int r, int g, int b)
{
    return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
int find_inter(t_ray *ray, t_sphere *o)
{
    double hold;
    hold = 0.0;
    // while (obj)
    //{

    hold = sphereIntesection(ray, o);
    // obj = obj->next;
    //}
    return (hold);
}
void draw(t_scene *scene)
{
    int i;
    int j;
    double u;
    double v;
    //t_inter in;
    t_v3 color;
    t_ray r;

    j = H - 1;
    color = (t_v3){scene->ambient_color.red * scene->ambient_intensity, scene->ambient_color.green * scene->ambient_intensity, scene->ambient_color.blue * scene->ambient_intensity};
    while (j >= 0)
    {
        i = 0;
        while (i < W)
        {
            v = (double)i * 2 / W - 1;
            u = (double)j * 2 / H - 1;
            r = calculateRay(scene->camera, v, u);
            // printf("r.direction = %f %f %f\n", r.direction.x, r.direction.y, r.direction.z);
            // exit(0);
            //in = inter(&r, scene->sphere);
            // if (in.t >= 0.0)
            // {
            //     color = (t_v3){scene->sphere->color.red, scene->sphere->color.green, scene->sphere->color.blue};
            //      color = (t_v3){color.x + scene->ambient_color.red *  scene->ambient_intensity, color.y + scene->ambient_color.green * scene->ambient_intensity, color.z + scene->ambient_color.blue * scene->ambient_intensity};
            //    // color = add_vectors(color, add_light(scene->light, &in));
            // }
            if(inter_plane(&r,scene->plane) > 0)
                color = scene->plane->color;
            else
                //color = (t_v3){0.0, 0.0, 0.0};
            color = (t_v3){scene->ambient_color.red * scene->ambient_intensity, scene->ambient_color.green * scene->ambient_intensity, scene->ambient_color.blue * scene->ambient_intensity};
            put_pixel(scene->image, i, j, rgb_to_int(&color));
            i++;
        }
        j--;
    }
}
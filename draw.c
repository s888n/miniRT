#include "rt.h"
int create_rgb(int r, int g, int b)
{
    return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

double findIntersection(t_ray *r, t_object *objs)
{
    while (objs)
    {

        if (objs->type == SPHERE)
            return (sphereIntersection(r, (t_sphere *)objs->ptr));
        if (objs->type == PLANE)
            return (planeIntersection(r, (t_plane *)objs->ptr));
        if (objs->type == CYLINDER)
            return (cylinderIntersection(r, (t_cylinder *)objs->ptr));
        objs = objs->next;
    }
    return (-1);
}
void draw(t_scene *scene)
{
    int i;
    int j;
    double u;
    double v;
    double t = -1;
    // t_interesect in;
    t_v3 color;
    t_ray r;

    j = H - 1;
    color = (t_v3){scene->ambient_color.x * scene->ambient_intensity, scene->ambient_color.y * scene->ambient_intensity, scene->ambient_color.z * scene->ambient_intensity};
    while (j >= 0)
    {
        i = 0;
        while (i < W)
        {
            v = (double)i * 2 / W - 1;
            u = (double)j * 2 / H - 1;
            r = calculateRay(scene->camera, v, u);
            t = findIntersection(&r, scene->objects);
            if (t > 0)
                color = (t_v3){255, 0,0};
            if (t < 0)
                color = (t_v3){scene->ambient_color.x * scene->ambient_intensity, scene->ambient_color.y * scene->ambient_intensity, scene->ambient_color.z * scene->ambient_intensity};
            put_pixel(scene->image, i, H - j - 1, rgb_to_int(&color));
            i++;
        }
        j--;
    }
}
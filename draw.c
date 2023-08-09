#include "rt.h"
int create_rgb(int r, int g, int b)
{
    return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}


double findIntersection(t_ray *r, t_object *objs)
{
    t_object *o;
    t_interesect in;
    o = objs;

    in.t = -1;
    while (o)
    {
        if (o->type == SPHERE)
            return (sphereIntersection(r, (t_sphere *)o->ptr));
        if (o->type == PLANE)
            return (planeIntersection(r, (t_plane *)o->ptr));
        if (o->type == CYLINDER)
            return (cylinderIntersection(r, (t_cylinder *)o->ptr));
        o = o->next;
    }
    return (-1);
}
void draw(t_scene *scene)
{
    int i;
    int j;
    double u;
    double v;
    t_v3 color;
    t_ray r;

    j = H - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < W)
        {
            v = (double)i * 2 / W - 1;
            u = (double)j * 2 / H - 1;
            r = calculateRay(scene->camera, v, u);
            color = get_color(&r, scene);
            put_pixel(scene->image, i, H - j - 1, rgb_to_int(&color));
            i++;
        }
        j--;
    }
}
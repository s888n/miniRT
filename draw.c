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
t_interesect find_intersection(t_ray *ray, t_scene *scene)
{
    t_interesect in;
    t_list *o;

    o = scene->objects;
    t_object *obj;
    in.t = -1;
    while (o)
    {
        obj = (t_object *)o->content;
        if (obj->type == SPHERE)
        {
            in.t = sphereIntesection(ray, obj->ptr);
            in.color = (t_v3){obj->color.red, obj->color.green, obj->color.blue};
        }
        else if (obj->type == CYLINDER)
        {
            in.t = cylinderIntersection(ray, obj->ptr);
            in.color = (t_v3){obj->color.red, obj->color.green, obj->color.blue};
        }
        else if (obj->type == PLANE)
        {
            in.t = inter_plane(ray, obj->ptr);
            in.color = (t_v3){obj->color.red, obj->color.green, obj->color.blue};
        }
        printf("t = %f\n", in.t);
        o = o->next;
    }
    return (in);
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
    color = (t_v3){scene->ambient_color.red * scene->ambient_intensity, scene->ambient_color.green * scene->ambient_intensity, scene->ambient_color.blue * scene->ambient_intensity};
    while (j >= 0)
    {
        i = 0;
        while (i < W)
        {
            v = (double)i * 2 / W - 1;
            u = (double)j * 2 / H - 1;
            r = calculateRay(scene->camera, v, u);
            // in = find_intersection(&r, scene);
            //t = inter_plane(&r, scene->plane);
            // t = sphereIntesection(&r, scene->sphere);
             t = cylinderIntersection(&r, scene->cylinder);
             if(t > 0)
            color = (t_v3){0,55,66};
            if (t < 0)
                color = (t_v3){scene->ambient_color.red * scene->ambient_intensity, scene->ambient_color.green * scene->ambient_intensity, scene->ambient_color.blue * scene->ambient_intensity};
            put_pixel(scene->image, i, j, rgb_to_int(&color));
            i++;
        }
        j--;
    }
}
#include "rt.h"
t_v3 difuse_light(t_interesect *in, t_scene *scene)
{
    t_v3 difuse;

    double d;
    d = dot(scene->light->direction, in->normal);
    if (d > 0)
        difuse = multi_vec_by_n(scene->light->color, scene->light->intensity * d *0.5);
    else
        difuse = (t_v3){0, 0, 0};
    return (difuse);
}
t_v3 reflect_vec(t_v3 l, t_v3 n)
{
    t_v3 r;

    r = multi_vec_by_n(n, 2 * dot(l, n));
    r = minus_vectors(r, l);
    return (r);
}
t_v3 specular_light(t_interesect *in, t_scene *scene)
{
    t_v3 reflect_dir;
    t_v3 view_dir;
    double d;

    reflect_dir = reflect_vec(scene->light->direction, in->normal);
    view_dir = normalize(minus_vectors(scene->camera->origin, in->hit_point));
    d = pow(fmax(0.0,dot(reflect_dir, view_dir)),SHINE);
    return multi_vec_by_n(scene->light->color,scene-> light->intensity * d);
}

int shade(t_interesect *in, t_scene *scene)
{
    t_ray shade_ray;
    t_interesect shade_in;

     shade_ray.origin = add_vectors(in->hit_point, multi_vec_by_n(in->normal, BIAS));
    shade_ray.direction = normalize(minus_vectors(scene->light->p0, in->hit_point));
    shade_in = get_intersection(&shade_ray, scene->objects);
    if (shade_in.t > 0 && vec_len(minus_vectors(scene->light->p0\
    , in->hit_point)) > vec_len(minus_vectors(in->hit_point\
    , shade_in.hit_point))+BIAS)
        return (1);
    return (0);
}

t_v3 add_light(t_v3 color, t_interesect *in, t_scene *scene)
{
    // t_v3 light_dir;
    t_v3 ambiant;
    t_v3 difuse;
    t_v3 specular;
    t_v3 light_color;

    ambiant = multi_vec_by_n(scene->ambient_color, scene->ambient_intensity);
    scene->light->direction = normalize(minus_vectors(scene->light->p0, in->hit_point));
    scene->light->distance = vec_len(minus_vectors(scene->light->p0, in->hit_point));
    difuse = difuse_light(in, scene);
    specular = specular_light(in, scene);
    light_color = add_vectors(ambiant, add_vectors(difuse, specular));
    if (shade(in, scene))
        return multi_vectors(color, ambiant);
    else
        return multi_vectors(color, light_color);
}
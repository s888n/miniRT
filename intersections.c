#include "rt.h"
#define BIAS 0.000001
#define SHINE 32
t_interesect get_sphere(t_ray *r, t_sphere *s, t_interesect in)
{
    t_interesect i;

    i.t = sphereIntersection(r, s);
    if (i.t > 0 && (in.t < 0 || i.t < in.t))
    {
        i.color = s->color;
        i.hit_point = add_vectors(r->origin, multi_vec_by_n(r->direction, i.t));
        i.normal = normalize(minus_vectors(i.hit_point, s->center));
        in = i;
    }
    return (in);
}

t_interesect get_plane(t_ray *r, t_plane *p, t_interesect in)
{
    t_interesect i;

    i.t = planeIntersection(r, p);
    if (i.t > 0 && (in.t < 0 || i.t < in.t))
    {
        i.color = p->color;
        i.hit_point = add_vectors(r->origin, multi_vec_by_n(r->direction, i.t));
        i.normal = p->normal;
        // we only care about the angle between the light and the normal
        if (dot(i.normal, r->direction) > 0)
            i.normal = multi_vec_by_n(i.normal, -1);
        in = i;
    }
    return (in);
}

t_interesect get_cylinder(t_ray *r, t_cylinder *c, t_interesect in)
{

    t_interesect i;
    t_interesect i2;
    t_interesect i3;
    t_plane p;
    t_plane p1;
    t_v3 pc1;
    t_v3 pc2;
    double d;

    p.normal = c->normal;
    p.p0 = c->top_cap_center;
    p1.normal = c->normal;
    p1.p0 = c->bottom_cap_center;

    i.t = cylinderIntersection(r, c);
    i2.t = planeIntersection(r, &p);
    i3.t = planeIntersection(r, &p1);
    pc1 = add_vectors(r->origin, multi_vec_by_n(r->direction, i2.t));
    pc2 = add_vectors(r->origin, multi_vec_by_n(r->direction, i3.t));
    if (i2.t > 0 && vec_len(minus_vectors(pc1, c->top_cap_center)) <= c->radius)
    {
        in.t = i2.t;
        in.normal = p.normal;
        in.hit_point = pc1;
        in.color = c->color;
    }

    if (i3.t > 0 && vec_len(minus_vectors(pc2, c->bottom_cap_center)) <= c->radius)
    {
        in.t = i3.t;
        in.normal = c->normal;
        in.hit_point = pc2;
        in.color = c->color;
    }
    if (i.t > 0 && (in.t < 0 || i.t < in.t))
    {
        i.color = c->color;
        i.hit_point = add_vectors(r->origin, multi_vec_by_n(r->direction, i.t));
        d = dot(c->normal, minus_vectors(i.hit_point, c->bottom_cap_center));
        if (d < 0 || d > c->height)
            return (in);
        i.normal = normalize(minus_vectors(minus_vectors(i.hit_point, c->p), multi_vec_by_n(c->normal, dot(minus_vectors(i.hit_point, c->p), c->normal))));
        in = i;
    }

    return in;
}

t_interesect get_intersection(t_ray *r, t_object *objs)
{
    t_object *o;
    t_interesect in;

    o = objs;
    in.t = -1;
    while (o)
    {
        if (o->type == SPHERE)
            in = get_sphere(r, (t_sphere *)o->ptr, in);
        if (o->type == PLANE)
            in = get_plane(r, (t_plane *)o->ptr, in);
        if (o->type == CYLINDER)
            in = get_cylinder(r, (t_cylinder *)o->ptr, in);
        o = o->next;
    }
    return (in);
}
t_v3 difuse_light(t_interesect *in, t_scene *scene)
{
    t_v3 difuse;
    t_v3 light_dir;
    double d;

    light_dir = normalize(minus_vectors(scene->light->p0, in->hit_point));
    d = dot(light_dir, in->normal);
    if (d > 0)
        difuse = multi_vec_by_n(scene->light->color, scene->light->intensity * d);
    else
        difuse = (t_v3){0, 0, 0};
    return (difuse);
}
t_v3 reflect_vec(t_v3 l, t_v3 n)
{
    t_v3 r;

    r = multi_vec_by_n(n, 2 * dot(l, n));
    r = minus_vectors(l, r);
    return (r);
}
t_v3 specular_light(t_interesect *in, t_scene *scene)
{
    t_v3 specular;
    t_v3 light_dir;
    t_v3 reflect_dir;
    t_v3 view_dir;
    double d;

    light_dir = normalize(minus_vectors(in->hit_point, scene->light->p0));
    reflect_dir = reflect_vec(light_dir, in->normal);
    view_dir = normalize(minus_vectors(scene->camera->origin, in->hit_point));
    d = dot(reflect_dir, view_dir);
    if (d > 0)
        specular = multi_vec_by_n(scene->light->color, scene->light->intensity * pow(d, SHINE));
    else
        specular = (t_v3){0, 0, 0};
    return (specular);
}

int shade(t_interesect *in, t_scene *scene)
{
    t_ray shade_ray;
    t_interesect shade_in;

     shade_ray.origin = add_vectors(in->hit_point, multi_vec_by_n(in->normal, BIAS));
    shade_ray.direction = normalize(minus_vectors(scene->light->p0, in->hit_point));
    shade_in = get_intersection(&shade_ray, scene->objects);
    if (shade_in.t > 0 && vec_len(minus_vectors(scene->light->p0, in->hit_point)) > vec_len(minus_vectors(in->hit_point, shade_in.hit_point))+BIAS)
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
    difuse = difuse_light(in, scene);
    specular = specular_light(in, scene);
    light_color = add_vectors(ambiant, add_vectors(difuse, specular));
    if (shade(in, scene))
        return multi_vectors(color, ambiant);
    else
        return multi_vectors(color, light_color);
}

t_v3 get_color(t_ray *r, t_scene *scene)
{
    t_interesect in;
    t_v3 color;
    in = get_intersection(r, scene->objects);
    if (in.t > 0)
    {
        color = in.color;
        if (dot(in.normal, r->direction) > 0)
            in.normal = multi_vec_by_n(in.normal, -1);
        color = add_light(color, &in, scene);
        return (color);
    }
    return (multi_vec_by_n(scene->ambient_color, scene->ambient_intensity));
}
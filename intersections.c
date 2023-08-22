#include "rt.h"

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
t_interesect cy_top_cap(t_ray *r,t_cylinder *c ,t_interesect in)
{
    t_interesect i;
    t_plane p;
    t_v3 cp;

    p.normal = c->normal;
    p.p0 = c->top_cap_center;
    i.t = planeIntersection(r, &p);
    if (i.t > 0 && (in.t < 0 || i.t < in.t))
    {
        cp = minus_vectors(add_vectors(r->origin, multi_vec_by_n(r->direction, i.t)), c->top_cap_center);
        if (dot(cp, cp) <= c->radius * c->radius)
        {
            i.color = c->color;
            i.hit_point = add_vectors(r->origin, multi_vec_by_n(r->direction, i.t));
            i.normal = p.normal;
            in = i;
        }
    }
    return (in);
}
t_interesect cy_btm_cap(t_ray *r,t_cylinder *c,t_interesect in)
{
    t_interesect i;
    t_v3 cp;
    t_plane p;
    p.normal = multi_vec_by_n (c->normal, -1);
    p.p0 = c->bottom_cap_center;
    i.t = planeIntersection(r, &p);
    if (i.t > 0 && (in.t < 0 || i.t < in.t))
    {
        cp = minus_vectors(add_vectors(r->origin, multi_vec_by_n(r->direction, i.t)), c->bottom_cap_center);
        if (dot(cp, cp) <= c->radius * c->radius)
        {
            i.color = c->color;
            i.hit_point = add_vectors(r->origin, multi_vec_by_n(r->direction, i.t));
            i.normal = p.normal;
            in = i;
        }
    }
    return (in);
}
t_interesect cylinder(t_ray *r, t_cylinder *c, t_interesect in)
{

    t_interesect i; 
    double d;

    i.t = cylinderIntersection(r, c);
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
t_interesect get_cylinder(t_ray *r, t_cylinder *c, t_interesect in)
{
    t_interesect i;
    t_interesect top;
    t_interesect btm;

    i = cylinder(r, c, in);
    top = cy_top_cap(r, c,in);
    btm = cy_btm_cap(r, c,in);
    if (top.t > 0 && (i.t < 0 || top.t < i.t))
        i = top;
    if (btm.t > 0 && (i.t < 0 || btm.t < i.t))
        i = btm;
    return (i);
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
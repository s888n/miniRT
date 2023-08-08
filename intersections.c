#include "rt.h"

t_interesect get_sphere(t_ray *r , t_sphere *s , t_interesect in)
{
    t_interesect i;

    i.t = sphereIntersection(r , s);
    if(i.t > 0 && (in.t < 0 || i.t < in.t))
    {
        i.color = s->color;
        i.hit_point = add_vectors(r->origin , multi_vec_by_n(r->direction , i.t));
        i.normal = normalize(minus_vectors(i.hit_point , s->center));
        in = i;
    }
    return (in);
}

t_interesect get_plane(t_ray *r , t_plane *p , t_interesect in)
{
    t_interesect i;
   // double t;

    i.t = planeIntersection(r , p);
    if(i.t > 0 && (in.t < 0 || i.t < in.t))
    {
        i.color = p->color;
        i.hit_point = add_vectors(r->origin , multi_vec_by_n(r->direction , i.t));
        i.normal = p->normal;
        //we only care about the angle between the light and the normal
        if (dot(i.normal , r->direction) > 0)
            i.normal = multi_vec_by_n(i.normal , -1);
        in = i;
    }
    return (in);

}

t_interesect get_cylinder(t_ray *r , t_cylinder *c , t_interesect in)
{
    //t_v3 oc;
    //double n;
    t_interesect i;
    i.t = cylinderIntersection(r , c);
    if(i.t > 0 && (in.t < 0 || i.t < in.t))
    {
        i.color = c->color;
        i.hit_point = add_vectors(r->origin , multi_vec_by_n(r->direction , i.t));

        i.normal = normalize(minus_vectors(minus_vectors(i.hit_point , c->p) , multi_vec_by_n(c->normal , dot(minus_vectors(i.hit_point , c->p) , c->normal))));
        in = i;
    }
    return in;
}

t_interesect get_intersection(t_ray *r , t_object *objs)
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
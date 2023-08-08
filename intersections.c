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

t_v3 add_light(t_v3 color , t_interesect *in,t_scene *scene)
{
    t_v3 black;
    t_v3 light_dir;
    black = (t_v3){0,0,0};
    light_dir = normalize(minus_vectors(scene->light->p0 , in->hit_point));
    // if(dot(light_dir, in->normal) > 0)
    // {
    //     t_ray shadow_ray;
    //     t_interesect shadow_in;
    //     shadow_ray.origin = in->hit_point;
    //     shadow_ray.direction = light_dir;
    //     shadow_in = get_intersection(&shadow_ray , scene->objects);
    //     if(shadow_in.t < 0)
    //     {
    //         //double light_intensity;
    //         color = add_vectors(color , multi_vec_by_n(multi_vectors(in->color , scene->light->color) , scene->light->intensity * dot(light_dir , in->normal)));
    //     }
    // }
    black = color;
    if(dot(light_dir , in->normal) > 0)
    {
        black = add_vectors(black , multi_vec_by_n(multi_vectors(in->color , scene->light->color) , scene->light->intensity * dot(light_dir , in->normal)));
    }
    return (black);
}
t_v3 get_color(t_ray *r , t_scene *scene)
{
    t_interesect in;
    t_v3 color;
    in = get_intersection(r , scene->objects);
    if (in.t > 0)
    {
        color = multi_vectors(in.color , multi_vec_by_n(scene->ambient_color , scene->ambient_intensity));
        if(dot(in.normal , r->direction) > 0)
            in.normal = multi_vec_by_n(in.normal , -1);
        color  = add_light(color , &in , scene);
        return (color); 
    }
    return (multi_vec_by_n(scene->ambient_color , scene->ambient_intensity));
}
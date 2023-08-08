#include "rt.h"

double sphereIntersection(t_ray *r, t_sphere *s)
{
    double a;
    double b;
    double c;
    double delta;
    double t1;
    double t2;
    t_v3 oc;
    oc = minus_vectors(r->origin, s->center);
    a = dot(r->direction, r->direction);
    b = 2 * dot(oc, r->direction);
    c = dot(oc, oc) - pow(s->radius, 2);
    delta = pow(b, 2) - (4 * a * c);
    if (delta < 0)
        return (-1);
    t1 = (-b - sqrt(delta)) / (2 * a);
    t2 = (-b + sqrt(delta)) / (2 * a);
    if (t1 < 0 && t2 < 0)
        return (-1);
    if (t1 < 0)
        return (t2);
    if (t2 < 0)
        return (t1);
    return (t1 < t2 ? t1 : t2);
}

double planeIntersection(t_ray *r , t_plane *p)
{
    t_v3 n;
    t_v3 c;
    double t;
    double d;
    double a;


    c = minus_vectors(r->origin, p->p0);
    n = normalize(p->normal);
    t = dot(r->direction, n);
    if(t != 0)
    {
        d = dot(c,n);
        a = -d / t;
        if(a < 0.000001)
            return (-1);
        return (a);
    }
    return (-1.0);
}
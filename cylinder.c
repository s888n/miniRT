#include "rt.h"

double cylinderIntersection(t_ray *r, t_cylinder *cy)
{
    double a;
    double b;
    double c;
    double delta;
    double t1;
    double t2;
    t_v3 oc;
    oc = minus_vectors(r->origin, cy->p);
    a = dot(r->direction, r->direction) - pow(dot(r->direction, cy->normal), 2);
    b = 2 * (dot(oc, r->direction) - (dot(oc, cy->normal) * dot(r->direction, cy->normal)));
    c = dot(oc, oc) - pow(dot(oc, cy->normal), 2) - pow(cy->radius, 2);
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
    return (-1);
}
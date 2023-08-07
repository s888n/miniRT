#include "rt.h"

double cylinderIntersection(t_ray *r, t_cylinder *cy)
{
    double a;
    double b;
    double c;
    double delta;
    double t1;
    double t2;
    double y0;
    double y1;
    t_v3 oc;
    //oc is the vector from the center of the sphere to the origin of the ray
    oc = minus_vectors(r->origin, cy->p);
    //a is the dot product of the direction of the ray and itself minus the dot product of the direction of the ray and the normal of the sphere squared
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
    y0 = dot(r->origin, cy->normal) + t1 * dot(r->direction, cy->normal);
    y1 = dot(r->origin, cy->normal) + t2 * dot(r->direction, cy->normal);
    if(y0 <= cy->height && y0 > 0)
        return (t1);
    if(y1 <= cy->height && y1 > 0)
        return (t2);
    return (-1);
}
#include "rt.h"

t_ray calculateRay(t_camera *c, double u, double v)
{
    t_ray r;
    r.origin = c->origin;
    r.direction = normalize(minus_vectors(add_vectors (add_vectors(c->btm_lft,\
     multi_vec_by_n(c->horizontal, u)), multi_vec_by_n (c->vertical, v)), c->origin));
    return r;
}
#include "rt.h"

t_ray calculateRay(t_camera *c, double v, double u)
{
    t_ray r;
    r.origin = c->origin;
    r.direction = add_vectors(add_vectors(multi_vec_by_n(c->up, v * c->vp_h), multi_vec_by_n(c->right, u * c->vp_w)), c->forward);
    r.direction = normalize(r.direction);
    return r;
}
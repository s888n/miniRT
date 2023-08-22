#include "rt.h"
t_v3 scale_v3(t_v3 v, double t)
{
    return ((t_v3){v.x * t, v.y * t, v.z * t});
}
t_v3 add_v3(t_v3 v1, t_v3 v2)
{
    return ((t_v3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}
t_v3 sub_v3(t_v3 v1, t_v3 v2)
{
    return ((t_v3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}
t_v3 v3(double x, double y, double z)
{
    return ((t_v3){x, y, z});
}
int v3_equal(t_v3 v1, t_v3 v2)
{
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}
static t_v3 v3_up(t_v3 v)
{
    if (v3_equal(v, v3(0, 1, 0)))
        return (v3(0, 0, 1));
    if (v3_equal(v, v3(0, -1, 0)))
        return (v3(0, 0, -1));
    return (v3(0, 1, 0));
}
static  void get_up_right(t_v3 forward, t_v3 *up, t_v3 *right)
{
    *right = normalize(cross(v3_up(forward), forward));
    *up = normalize(cross(forward, *right));
}
t_camera *set_up_camera(t_camera *camera)
{
   
    camera->forward = normalize(scale_v3(camera->forward, -1));
    get_up_right(camera->forward, &camera->up, &camera->right);
    camera->theta = camera->fov * M_PI / 180.0;
    camera->aspect_ratio = (double)W / (double)H;
    camera->vp_w = 2.0 * tan(camera->theta / 2.0);
    camera->vp_h = camera->aspect_ratio * camera->vp_w;
    camera->horizontal = scale_v3(camera->right, camera->vp_w);
    camera->vertical = scale_v3(camera->up, camera->vp_h);
    camera->btm_lft = sub_v3(camera->origin,\
     add_v3(scale_v3(add_v3(camera->horizontal, camera->vertical), 1.0 / 2.0), camera->forward));
   return (camera);
}
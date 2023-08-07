#include "rt.h"

// t_inter inter(t_ray *r,t_sphere *s)
// {
//     t_inter i;
//     i.t = -1;
//     i.t = sphereIntesection(r,s);
//     if(i.t > 0)
//     {
//         i.hit_point = add_vectors(r->origin, multi_vec_by_n(r->direction, i.t));
//         i.normal = normalize(minus_vectors(i.hit_point, s->center));
//         i.color = (t_color2){i.normal.x * 0.5 + 0.5, i.normal.y * 0.5 + 0.5, i.normal.z * 0.5 + 0.5};
//     }

//     return i;
// }
// t_v3 add_light(t_light *light , t_inter *inter)
// {
//     t_v3 ldir;
//     t_v3 color;

//     ldir = normalize(minus_vectors(light->p0, inter->hit_point));
//     double d = dot(ldir, inter->normal);
//     if(d > 0)
//     {
//         color = multi_vec_by_n((t_v3){light->color.red,light->color.green,light->color.blue}, d);
//         return color;
//     }
//     else return (t_v3){0,0,0};
// }
double		inter_plane(t_ray *ray, t_plane *pl)
{
	t_v3	x;
	t_v3	normal;
	double	t;
	double	b;
	double	a;

	normal = normalize(pl->normal);
	x = minus_vectors(ray->origin, pl->p0);
	b = dot(ray->direction, normal);
	if (b != 0)
	{
		a = dot(x, normal);
		t = -a / b;
		if (t < 0.000001)
			return (-1.0);
		return (t);
	}
	return (-1.0);
}
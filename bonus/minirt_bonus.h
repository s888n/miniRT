/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:59:59 by srachdi           #+#    #+#             */
/*   Updated: 2023/08/27 13:43:14 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define WHITE "\033[1;39m"
# define RESET "\033[0m"
# define W 1024
# define H 1024
# define BIAS 1e-6
# define SHINE 32
# define ESC 53

typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_cone		t_cone;

typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

typedef struct s_uv
{
	double	u;
	double	v;
}	t_uv;

typedef struct s_abc
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;
}	t_abc;

typedef struct s_camera
{
	t_v3	origin;
	t_v3	forward;
	double	fov;
	double	theta;
	double	aspect_ratio;
	double	vp_h;
	double	vp_w;
	t_v3	up;
	t_v3	right;
	t_v3	horizontal;
	t_v3	vertical;
	t_v3	btm_lft;
}	t_camera;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
}	t_otype;

typedef struct s_object
{
	t_otype			type;
	void			*ptr;
	t_v3			color;
	struct s_object	*next;
}	t_object;

typedef struct s_light
{
	t_v3			p0;
	double			intensity;
	t_v3			color;
	t_v3			direction;
	double			distance;
	struct s_light	*next;
}	t_light;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_texture
{
	void	*mlx;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_scene
{
	t_object	*objects;
	t_light		*lights;
	double		ambient_intensity;
	t_v3		ambient_color;
	t_camera	*camera;
	t_image		*image;
	int			i;
	int			j;
	double		u;
	double		v;
	void		*mlx;

}	t_scene;

typedef struct s_info
{
	t_scene	*scene;
	void	*mlx;
	void	*window;
	t_image	image;
}	t_info;

typedef struct s_sphere
{
	t_v3		center;
	double		radius;
	t_v3		color;
	t_v3		color2;
	int			has_pattern;
	int			has_bump;
	t_texture	bump;
}	t_sphere;

typedef struct s_cylinder
{
	t_v3	p;
	t_v3	normal;
	double	radius;
	double	height;
	t_v3	color;
	t_v3	color2;
	int		has_pattern;
	t_v3	top_cap_center;
	t_v3	bottom_cap_center;
}	t_cylinder;

typedef struct s_plane
{
	t_v3	p0;
	t_v3	normal;
	t_v3	color;
	t_v3	color2;
	int		has_pattern;
}	t_plane;

typedef struct s_cone
{
	t_v3	center;
	t_v3	tip;
	t_v3	axis;
	t_v3	normal;
	double	radius;
	double	height;
	t_v3	color;
	t_v3	color2;
	int		has_pattern;
}	t_cone;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
}	t_ray;

typedef struct s_intersect
{
	double	t;
	t_v3	color;
	t_v3	hit_point;
	t_v3	normal;
	t_otype	type;
	int		has_pattern;
	void	*shape;
	t_uv	uv;
}	t_interesect;

int				ft_isdigit(int c);
char			**ft_split(char const *s1, char c);
double			ft_atod(char *n);
t_scene			*parse(char *filename);
int				arrlen(char **arr);
void			init_scene(t_scene *scene);
int				openfile(char *filename);
void			parse_error(char *errmsg, int e_n);
void			norm_victor(t_v3 *v);
int				valid_color(t_v3 color);
void			parse_color(t_v3 *clr, char *field);
void			parse_coords(t_v3 *point, char *field);
void			ambient(t_scene *scene, char **arr);
void			camera(t_scene *scene, char **arr);
void			light(t_scene *scene, char **arr);
void			pl(t_scene *scene, char **arr);
void			sp(t_scene *scene, char **arr);
void			cy(t_scene *scene, char **arr);
void			cn(t_scene *scene, char **arr);
int				allowedchars(char c);
int				validfilename(char *filename);
void			put_pixel(t_image *image, int x, int y, int color);
int				rgb_to_int(t_v3 *color);
double			vec_len(t_v3 vec);
t_v3			add_vectors(t_v3 vec1, t_v3 vec2);
t_v3			add_vec_a_b_c(t_v3 vec, double a, double b, double c);
t_v3			minus_vectors(t_v3 vec1, t_v3 vec2);
t_v3			minus_vec_a_b_c(t_v3 vec, double a, double b, double c);
t_v3			multi_vectors(t_v3 vec1, t_v3 vec2);
t_v3			multi_vec_by_n(t_v3 vec, double n);
t_v3			divide_vec_by_n(t_v3 vec, double n);
double			dot(t_v3 vec1, t_v3 vec2);
t_v3			cross(t_v3 vec1, t_v3 vec2);
t_v3			normalize(t_v3 vec);
t_ray			calculate_ray(t_camera *c, double u, double v);
t_camera		*set_up_camera(t_camera *c);
void			draw(t_scene *scene);
double			sphere_intersection(t_ray *r, t_sphere *s);
double			plane_intersection(t_ray *r, t_plane *p);
double			cylinder_intersection(t_ray *r, t_cylinder *cy);
double			cone_intersection(t_ray *r, t_cone *cone);
t_interesect	get_plane(t_ray *r, t_plane *p, t_interesect in);
t_interesect	get_sphere(t_ray *r, t_sphere *s, t_interesect in);
t_interesect	get_cylinder(t_ray *r, t_cylinder *cy, t_interesect in);
t_interesect	get_cone(t_ray *r, t_cone *cone, t_interesect in);
t_interesect	min_positive_in(t_interesect i1, \
				t_interesect i2, t_interesect i3);
void			add_to_objs_list(t_object **head, t_object *n);
t_object		*new_object(t_otype type, void *ptr);
t_interesect	get_intersection(t_ray *r, t_object *objs);
t_v3			get_color(t_ray *r, t_scene *scene);
t_interesect	get_cone(t_ray *r, t_cone *cone, t_interesect in);
t_v3			get_pattern(t_interesect *in);
int				color_or_texture(char *s);
void			add_to_light_list(t_light **light, t_light *new);
int				clamp_uv(int value, int min, int max);
t_v3			int_to_rgb(int color);
t_texture		load_texture(char *path);
int				check_file(char *path);
t_uv			sphere_uv(t_sphere *s, t_interesect *i);
t_v3			get_bump(t_texture *t, t_uv uv);
t_v3			add_lights(t_v3 color, t_interesect *in, t_scene *scene);
void			free_arr(char **arr);
int				close_window(t_info *info);
int				esc_and_x_hook(t_info *info);
int				check_double(char *s, int n);
void			free_scene(t_scene *scene);
t_v3			reflect_vec(t_v3 l, t_v3 n);
void			spacer(char *s);
void			cn_patt(t_cone *cone, char *arr);
void			cy_patt(t_cylinder *cylinder, char *arr);
void			free_sphere(t_sphere *sphere);
void			invalid_shape(char *s, size_t n);
#endif

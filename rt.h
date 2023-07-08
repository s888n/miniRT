#ifndef RT_H
#define RT_H
#include <sys/types.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
// #include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#define RED	  \033[31m
#define GREEN \033[32m
#define BLUE  \033[34m
#define PINK  \033[35m
#define WHITE \033[37m
#define BOLD  \033[1m
#define RESET \033[0m
/*to be replaced with a user defined res*/
#define W 1000
/*to be replaced with a user defined res*/
#define H 1000
int err;
typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;
typedef struct s_color2
{
	float red;
	float green;
	float blue;
} t_color2;
typedef struct s_v3
{
	double x;
	double y;
	double z;
} t_v3;
typedef struct s_camera
{
	t_v3 origin;
	t_v3 direction;
	int fov;
} t_camera;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	LIGHT,
	CYLINDER,
} t_otype;

typedef struct s_object
{
	t_otype type;
	void *ptr;
	t_color2 color;
	double albedo;

} t_object;

typedef struct s_light
{
	t_v3 p0;
	double intensity;
	t_color2 color;
} t_light;
typedef struct s_scene
{
	t_list *objects;
	t_list *lights;
	int width;
	int height;
	double ambient_intensity;
	t_color2 ambient_color;
	t_list *cameras;
	int selected_camera;
} t_scene;
typedef struct s_image
{
	void *img;
	int *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_image;
typedef struct s_info
{
	t_scene *scene;
	int camera_number;
	void *id;
	void *window;
	t_image image;
} t_info;

typedef struct s_sphere
{
	t_v3 center;
	double radius;
} t_sphere;
typedef struct s_cylinder
{
	t_v3 p;
	t_v3 normal;
	double radius;
	double height;
} t_cylinder;
typedef struct s_plane
{
	t_v3 p0;
	t_v3 normal;
} t_plane;

int ft_isdigit(int c);
char **ft_split(char const *s1, char c);
void ft_lstadd_back(t_list **lst, t_list *new);
t_list *ft_lstnew(void *content);
t_scene *parse(char *filename);
int arrLen(char **arr);
void init_scene(t_scene *scene);
int openFile(char *filename);
void parseError(char *errmsg, int e_n);
void norm_victor(t_v3 *v);
int validColor(t_color2 color);
void parseColor(t_color2 *clr, char *field);
void parseCoords(t_v3 *point, char *field);
void ambient(t_scene *scene, char **arr);
void camera(t_scene *scene, char **arr);
void light(t_scene *scene, char **arr);
void pl(t_scene *scene, char **arr);
void sp(t_scene *scene, char **arr);
void cy(t_scene *scene, char **arr);
void checkScene(t_scene *scene);
int checkLine(char *line);
int allowedChars(char c);
int validFileName(char *filename);
void put_pixel(t_image *image, int x, int y, int color);
int rgb_to_int(t_color2 *color);
#endif
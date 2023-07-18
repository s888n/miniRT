#include "rt.h"
int close_window(t_info *info)
{
	mlx_destroy_window(info->id, info->window);
	exit(0);
}
t_camera *getCam(t_scene *s)
{
	t_camera *c;
	c = malloc(sizeof(t_camera));
	c->origin = s->camera->origin;
	c->forward = s->camera->forward;
	c->fov = s->camera->fov;
	c->aspect_ratio = (double)W / (double)H;
	c->theta = (double)c->fov * M_PI / 180;
	c->vp_h = tan(c->theta / 2.0);
	c->vp_w = c->aspect_ratio * c->vp_h;
	c->up = normalize(cross(c->forward, (t_v3){0.0, 1.0, 0.0}));
	c->right = normalize(cross(c->forward, c->up));
	return c;
}
void b(t_image *image,int color)
{
	int i;
	int j;
	j = 0;
	while (j < H)
	{
		i = 0;
		while (i < W)
		{
			put_pixel(image, i, j, color);
			i++;
		}
		j++;
	}
}
void init_mlx(t_info *info)
{
	info->id = mlx_init();
	info->window = mlx_new_window(info->id, W, H, "miniRT");
	info->image.img = mlx_new_image(info->id, W, H);
	info->image.addr = mlx_get_data_addr(info->image.img, &info->image.bits_per_pixel, &info->image.line_length, &info->image.endian);
	info->scene->image = &info->image;
	draw(info->scene);
	//b(&info->image, 0x00FF0000);
	mlx_put_image_to_window(info->id, info->window, info->image.img, 0, 0);
	mlx_loop(info->id);
}
void rt(const char *filename)
{
	t_info info;
	info.scene = parse((char *)filename);
	info.scene->camera = getCam(info.scene);
	init_mlx(&info);
}

int main(int ac, char const **av)
{

	if (ac == 2)
		rt(av[1]);
	else
	{
		printf("Error : \n ./rt [filename].rt");
		return 1;
	}
	return 0;
}

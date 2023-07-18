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
	printf("c->origin = %f %f %f\n", c->origin.x, c->origin.y, c->origin.z);
	c->forward = s->camera->forward;
	printf("c->forward = %f %f %f\n", c->forward.x, c->forward.y, c->forward.z);
	c->forward.x +=0.000001; 
	printf("c->forward = %f %f %f\n", c->forward.x, c->forward.y, c->forward.z);
	c->fov = s->camera->fov;
	printf("c->fov = %d\n", c->fov);
	c->aspect_ratio = (double)W / (double)H;
	printf("c->aspect_ratio = %f\n", c->aspect_ratio);
	c->theta = (double)c->fov * M_PI / 180;
	printf("c->theta = %f\n", c->theta);
	c->vp_h = tan(c->theta / 2.0);
	printf("c->vp_h = %f\n", c->vp_h);
	c->vp_w = c->aspect_ratio * c->vp_h;
	printf("c->vp_w = %f\n", c->vp_w);
	c->up = normalize(cross(c->forward, (t_v3){0.0, 1.0, 0.0}));
	printf("c->up = %f %f %f\n", c->up.x, c->up.y, c->up.z);
	c->right = normalize(cross(c->forward, c->up));
	printf("c->right = %f %f %f\n", c->right.x, c->right.y, c->right.z);
	return c;
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

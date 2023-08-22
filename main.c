#include "rt.h"
#include <sys/time.h>

int close_window(t_info *info)
{
	mlx_destroy_window(info->id, info->window);
	exit(0);
}

void init_mlx(t_info *info)
{
	struct timeval start, end;
	info->id = mlx_init();
	info->window = mlx_new_window(info->id, W, H, "miniRT");
	info->image.img = mlx_new_image(info->id, W, H);
	info->image.addr = mlx_get_data_addr(info->image.img, &info->image.bits_per_pixel, &info->image.line_length, &info->image.endian);
	info->scene->image = &info->image;
	gettimeofday(&start, NULL);
	draw(info->scene);
	gettimeofday(&end, NULL);
	printf("time to render :  %ld ms\n", (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	mlx_put_image_to_window(info->id, info->window, info->image.img, 0, 0);
	mlx_loop(info->id);
}
void rt(const char *filename)
{
	t_info info;
	//check_file(filename);
	info.scene = parse((char *)filename);
	info.scene->camera = set_up_camera(info.scene->camera);
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

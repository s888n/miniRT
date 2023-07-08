#include "rt.h"
int close_window(t_info *info)
{
	mlx_destroy_window(info->id,info->window);
	exit(0);
}
void rt(const char *filename)
{
	t_info info;
	info.scene = parse((char *)filename);
	printf("good parsing !!!\n");
	info.camera_number = 0;
	info.id = mlx_init();
	info.window = mlx_new_window(info.id, W, H, "miniRT");
	info.image.img = mlx_new_image(info.id, W, H);
	info.image.addr = (int *)mlx_get_data_addr(info.image.img,&info.image.bits_per_pixel,&info.image.line_length,&info.image.endian);
	mlx_hook(info.window,17,0,close_window,&info);
	
	mlx_loop(info.id);
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

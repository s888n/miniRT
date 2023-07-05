#include "rt.h"

void rt(const char *filename , int save)
{
	t_info info;
	info.scene = parse((char *)filename);
	printf("good parsing !!!\n");
}

int main(int ac, char const **av)
{
	if (ac < 2 || ac > 3)
		return (perror("too few or too many args"),1);
	else
	{
		if (ac == 2)
			rt(av[1], 0);
		else if (!strncmp("--save", av[2], strlen(av[2])))
			rt(av[1], 1);
	}
	return 0;
}

#include "rt.h"

void checkScene(t_scene *scene)
{
    if (!scene->cameras)
        parseError("no cam in scene\n", 17);
    if (scene->ambient_color.red < 0 || scene->ambient_color.green < 0 || scene->ambient_color.blue < 0)
        parseError("invalid ambient light\n",18);
    if(scene->width <= 0 || scene <= 0)
        parseError("invalid scene height or width\n", 19);
    if(scene->width > 5120 || scene->height > 2880)
        parseError("height or width too big\n", 20);//maybe allow it , by reassign the height an width to the maxscreen resulotion
}

int allowedChars(char c)
{
    if(c == ' ' || c == '\t' || c == '\n' || ft_isdigit(c) || c =='.' || c == ',' || c == '-')
        return 1;
    return 0;
}

int checkLine(char *line)
{
    int i = 0;
    while (line[i])
    {
        if(!allowedChars(line[i]) && i > 2)
            return (0);
        i++;
    }
    return (1);
}

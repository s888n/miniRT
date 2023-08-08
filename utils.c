#include "rt.h"

void checkScene(t_scene *scene)
{
    if (!scene->camera)
        parseError("no cam in scene\n", 17);
    if (scene->ambient_color.x < 0 || scene->ambient_color.y < 0 || scene->ambient_color.z < 0)
        parseError("invalid ambient light\n", 18);
    if (scene->width <= 0 || scene <= 0)
        parseError("invalid scene height or width\n", 19);
    if (scene->width > 5120 || scene->height > 2880)
        parseError("height or width too big\n", 20); // maybe allow it , by reassign the height an width to the maxscreen resulotion
}

int allowedChars(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || ft_isdigit(c) || c == '.' || c == ',' || c == '-')
        return 1;
    return 0;
}

int checkLine(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (!allowedChars(line[i]) && i > 2) // i should be 1 or 0 here
            return (0);
        i++;
    }
    return (1);
}

int countChar(char *s, char c)
{
    int count = 0;
    int i = -1;
    while (s[++i])
        if (s[i] == c)
            count++;
    return count;
}
int validFileName(char *filename)
{
    if (!strncmp(filename + (strlen(filename) - 3), ".rt", 3))
        return (1);
    return (0);
}

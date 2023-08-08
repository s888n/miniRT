#include "rt.h"
// A ,C ,L ,sp ,pl ,cy,
int arrLen(char **arr)
{
    int i = 0;
    while (arr[i])
        i++;
    return i;
}

int openFile(char *filename)
{
    int fd;
    if(strlen(filename) <= 3|| !validFileName(filename))
        parseError("invalid filename\n",1);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        parseError("error : couldn't open file\n", 1);
    return fd;
}

void init_scene(t_scene *scene)
{
    scene->camera = NULL;
    scene->light = NULL;
    scene->objects = NULL;
    scene->height = 0;
    scene->width = 0;
    scene->ambient_color.x = -1;
    scene->ambient_color.y = -1;
    scene->ambient_color.z = -1;
}
void parseLine(t_scene *scene, char **arr)
{
    if (arrLen(arr) == 0)
        return;
    else if (arrLen(arr) < 2)
        perror("error (1) in parseLine\n"), exit(2);
    if (!strncmp("A", arr[0], 1))
        ambient(scene, arr);
    else if (!strncmp("C", arr[0], 1))
        camera(scene, arr);
    else if (!strncmp("L", arr[0], 1))
        light(scene, arr);
    else if (!strncmp("sp", arr[0], 2))
        sp(scene, arr);
    else if (!strncmp("pl", arr[0], 2))
        pl(scene, arr);
    else if (!strncmp("cy", arr[0], 2))
        cy(scene, arr);
    else
        perror("error (2) in parseLine \n"), exit(3);
}

t_scene *parse(char *filename)
{
    int fd;
    char *line;
    char **arr;
    t_scene *scene;
    fd = openFile(filename);
    scene = malloc(sizeof(t_scene));
    init_scene(scene);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        arr = ft_split(line, ' ');
        if (!checkLine(line))
            parseError("unallowed char detected !!\n", 21);
        parseLine(scene, arr);
        free(line);
    }
    return (scene);
}
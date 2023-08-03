#include "rt.h"

void parseError(char *msg, int en)
{
    printf("%s",msg);
    exit(en);
}
void norm_victor(t_v3 *v)
{
    double len;
    len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= len;
    v->y /= len;
    v->z /= len;
}
int validColor(t_color2 color)
{
    if (color.red < 0 || color.red > 1 || color.green < 0 || color.green > 1 || color.blue < 0 || color.blue > 1)
        return 0;
    return 1;
}
void parseColor(t_color2 *clr, char *field)
{
    char **color;
    color = ft_split(field, ',');
    if (arrLen(color) != 3) // R , G , B
        parseError("R,G,B\n", 7);
    clr->red = (double)atoi(color[0]) / 255;
    clr->green = (double)atoi(color[1]) / 255;
    clr->blue = (double)atoi(color[2]) / 255;
}

void parseCoords(t_v3 *point, char *field)
{
    char **coords;
    coords = ft_split(field, ',');
    if (arrLen(coords) != 3)
        parseError("parseCoords : too few or too many args\n", 10);
    point->x = atof(coords[0]);
    point->y = atof(coords[1]);
    point->z = atof(coords[2]);
}

void ambient(t_scene *scene, char **arr)
{
    if (scene->ambient_color.red != -1)
        parseError("are you retarded ? you can only change once per scene\n", 4);
    if (arrLen(arr) != 3)
        parseError("usage : A   ratio   R,G,B\n", 5);
    scene->ambient_intensity = atof(arr[1]);
    if (scene->ambient_intensity < 0 || scene->ambient_intensity > 1)
        parseError("ratio is too high or too low or you're too high !!\n", 6);
    parseColor(&scene->ambient_color, arr[2]);
    if (!validColor(scene->ambient_color))
        parseError("color not valid\n", 8);
}

void camera(t_scene *scene, char **arr)
{
    t_camera *cam;

    if (arrLen(arr) != 4)
        parseError("usage : C   x,y,z   a,b,c   fov", 9);
    cam = malloc(sizeof(t_camera));
    parseCoords(&cam->origin, arr[1]);
    parseCoords(&cam->forward, arr[2]);
    norm_victor(&cam->forward);
    cam->fov = atoi(arr[3]);
    if (cam->fov < 0 || cam->fov > 180)
        parse("fov must be in this range =>[0, 180]\n");
    scene->camera = cam;
}

void light(t_scene *scene, char **arr)
{
    t_light *light;
    if (arrLen(arr) != 4)
        parseError("usage : L   x,y,z   brightness    R,G,B\n", 11);
    light = malloc(sizeof(t_light));
    parseCoords(&light->p0, arr[1]);
    light->intensity = atof(arr[2]);
    parseColor(&light->color, arr[3]);
    if (!validColor(light->color))
        parseError("color not valid\n", 12);
   scene->light = light;
}
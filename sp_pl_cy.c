#include "rt.h"


void sp(t_scene *scene , char **arr)
{   
    t_sphere *sphere;

    if(arrLen(arr) != 4)
        parseError("sphere : sp     x,y,z   diameter    R,G,B\n",13);
    sphere = malloc(sizeof(t_sphere));
    parseCoords(&sphere->center,arr[1]);
    sphere->radius = atof(arr[2]) / 2;
    parseColor(&sphere->color,arr[3]);
    if(!validColor(sphere->color))
        parseError("sphere ,invalid color\n",14);
    add_to_objs_list(&scene->objects,new_object(SPHERE,sphere));
}

void pl(t_scene *scene , char **arr)
{
    t_plane *plane;

    if(arrLen(arr) != 4)
        parseError("plane : pl     x,y,z   a,b,c    R,G,B\n",13);
    plane = malloc(sizeof(t_plane));
    parseCoords(&plane->p0,arr[1]);
    parseCoords(&plane->normal,arr[2]);
    norm_victor(&plane->normal);
    parseColor(&plane->color,arr[3]);
    if(!validColor(plane->color))
        parseError("plane : invalid color\n",15);
    add_to_objs_list(&scene->objects,new_object(PLANE,plane));
}

void cy(t_scene *scene , char **arr)
{
    t_cylinder *cylinder;

    if(arrLen(arr) != 6)
        parseError("cylinder : cy     x,y,z   a,b,c    diameter     height    R,G,B\n",13);
    cylinder = malloc(sizeof(t_cylinder));
    parseCoords(&cylinder->p,arr[1]);
    parseCoords(&cylinder->normal,arr[2]);
    norm_victor(&cylinder->normal);
    cylinder->radius = atof(arr[3]) / 2;
    cylinder->height = atof(arr[4]);
    parseColor(&cylinder->color,arr[5]);
    if(!validColor(cylinder->color))
        parseError("cylinder : invalid color\n",16);
    add_to_objs_list(&scene->objects,new_object(CYLINDER,cylinder));
}
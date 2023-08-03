#include "rt.h"

void sp(t_scene *scene , char **arr)
{   
    t_object *obj;
    t_sphere *sphere;

    if(arrLen(arr) != 4)
        parseError("sphere : sp     x,y,z   diameter    R,G,B\n",13);
    obj = malloc(sizeof(t_object));
    sphere = malloc(sizeof(t_sphere));
    parseCoords(&sphere->center,arr[1]);
    sphere->radius = atof(arr[2]) / 2;
    parseColor(&sphere->color,arr[3]);
    if(!validColor(obj->color))
        parseError("sphere ,invalid color\n",14);
    obj->type = SPHERE;
    obj->ptr = sphere;
    scene->sphere = sphere;
    ft_lstadd_back(&scene->objects,ft_lstnew(obj));
}

void pl(t_scene *scene , char **arr)
{
    t_object *obj;
    t_plane *plane;

    if(arrLen(arr) != 4)
        parseError("plane : pl     x,y,z   a,b,c    R,G,B\n",13);
    obj = malloc(sizeof(t_object));
    plane = malloc(sizeof(t_plane));
    parseCoords(&plane->p0,arr[1]);
    parseCoords(&plane->normal,arr[2]);
    norm_victor(&plane->normal);
    parseColor(&obj->color,arr[3]);
    if(!validColor(obj->color))
        parseError("plane : invalid color\n",15);
    obj->type = PLANE;
    obj->ptr = plane;
    plane->color = (t_v3){obj->color.red,obj->color.green,obj->color.blue};
    scene->plane = plane;

    ft_lstadd_back(&scene->objects,ft_lstnew(obj));
}

void cy(t_scene *scene , char **arr)
{
    t_object *obj;
    t_cylinder *cylinder;

    if(arrLen(arr) != 6)
        parseError("cylinder : cy     x,y,z   a,b,c    diameter     height    R,G,B\n",13);
    obj = malloc(sizeof(t_object));
    cylinder = malloc(sizeof(t_cylinder));
    parseCoords(&cylinder->p,arr[1]);
    parseCoords(&cylinder->normal,arr[2]);
    norm_victor(&cylinder->normal);
    cylinder->radius = atof(arr[3]) / 2;
    cylinder->height = atof(arr[4]);
    parseColor(&obj->color,arr[5]);
    if(!validColor(obj->color))
        parseError("cylinder : invalid color\n",16);
    obj->type = CYLINDER;
    obj->ptr = cylinder;
    ft_lstadd_back(&scene->objects,ft_lstnew(obj));
}
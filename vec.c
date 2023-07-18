#include "rt.h"
void change_vec(t_v3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}
/*returns the squared lenght of a vector , when we dont actualy need the lenght since using sqrt() can slow our program*/
double vec_len_square(t_v3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

/*returns the lenght of a vector*/
double vec_len(t_v3 vec)
{
	return (sqrt(vec_len_square(vec)));
}
/*adds 2 vectors THIS is correct vec1 does not change and it returns a new vector*/
t_v3 add_vectors(t_v3 vec1, t_v3 vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return vec1;
}

/*adds (a,b,c) to a vector*/
t_v3 add_vec_a_b_c(t_v3 vec, double a, double b, double c)
{
	vec.x += a;
	vec.y += b;
	vec.z += c;
	return (vec);
}

/*subtract vec2 from vec1 vectors*/
t_v3 minus_vectors(t_v3 vec1, t_v3 vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return vec1;
}

/*subtract (a,b,c) from a vector*/
t_v3 minus_vec_a_b_c(t_v3 vec, double a, double b, double c)
{
	vec.x -= a;
	vec.y -= b;
	vec.z -= c;
	return (vec);
}

/*multiple vec1 by vec2*/
t_v3 multi_vectors(t_v3 vec1, t_v3 vec2)
{
	vec1.x *= vec2.x;
	vec1.y *= vec2.y;
	vec1.z *= vec2.z;
	return vec1;
}
/*multiply a vector by n*/
t_v3 multi_vec_by_n(t_v3 vec, double n)
{

	vec.x *= n;
	vec.y *= n;
	vec.z *= n;
	return (vec);
}
/*devide a vector by n*/
t_v3 divide_vec_by_n(t_v3 vec, double n)
{
	vec.x *= 1 / n;
	vec.y *= 1 / n;
	vec.z *= 1 / n;
	return (vec);
}
/*returns the doc product of 2 vectors
Geometrically, the dot product is related to the angle between two vectors.
If the dot product of two vectors is positive,
 it means the vectors are pointing in a similar direction or are parallel.
  If the dot product is negative,
   it means the vectors are pointing in opposite directions or are anti-parallel.
   If the dot product is zero, the vectors are perpendicular to each other.
*/
double dot(t_v3 vec1, t_v3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
/*The cross product is used to determine a vector that is perpendicular to both input vectors,
 and its direction is determined by the right-hand rule.
  Geometrically, the magnitude of the cross product is equal to the area of
  the parallelogram formed by the two input vectors, and its direction is perpendicular
  to the plane spanned by the two vectors.*/
t_v3 cross(t_v3 vec1, t_v3 vec2)
{
	t_v3 v;

	v.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	v.y = (vec1.x * vec2.z) - (vec1.z * vec2.x);
	v.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return (v);
}
/*normalize a vector by ddivinding each(a,b,c) by the lenght of the vector*/
t_v3 normalize(t_v3 vec)
{
	double len = vec_len(vec);
	if (len == 0)
	{
		printf("Error\n:Devider is 0");
		exit(0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;

	return (vec);
}
/*return a victor that is the minimum of 2 vectors*/
t_v3 vmin(t_v3 vec1, t_v3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}
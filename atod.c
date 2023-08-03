#include "rt.h"

double ft_atod(char *n)
{
    double result = 0;
    double scale = 1;
    double sign = 1;
    int dot = 0;
    if (*n == '-')
        sign *= -1, n++;
    while (*n && ((*n >= '0' && *n <= '9') || *n == '.'))
    {
        if (dot)
        {
            scale = scale / 10;
            result = result + (*n - '0') * scale;
        }
        else if (*n == '.')
            dot++;
        else
            result = result * 10 + (*n - '0');
        n++;
    }
    return result * sign;
}
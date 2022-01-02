#include "libft.h"

int ft_str_is_num(char *str)
{
    int i;
    int len;

    i = 0;
    while (str[len])
        len++;
    while (str[i])
    {
        if ((str[i] < 48 || str[i] > 57 ) || (str[i] != '-'))
            break ;
        i++;
    }
    if (i == len)
        return (1);
    else
        return (0);
}
#include "../includes/main.h"

//; | < > space
char *msh_get_prev_word(char *str, int length, char *set)
{
	int i;
  
	i = length;
	while (i - 1 > -1 && !ft_strchr(set, str[i]))
		i--;
    return (ft_strndup(str + i, length + 1));
}

char *msh_get_next_word(char *str, int length, char *set)
{
	int i;

	i = length;
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
    return (ft_strndup(str + length,  i));
}

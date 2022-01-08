#include "../includes/main.h"

//; | < > space
char *msh_get_prev_word(char *str, int length, char *set)
{
	int i;
    int spaces;
  
    spaces = 0;
	i = length - 1;
    while (i - 1 > -1 && str[i] == ' ')
    {
        spaces++;
        i--;
    }
    while (i - 1 > -1 && !ft_strchr(set, str[i - 1]))
		i--;
    return (ft_strndup(str + i, length - i - spaces));
}

char *msh_get_next_word(char *str, int length, char *set)
{
	int i;
    int spaces;

    spaces = 0;
	i = length + 1;
    while (str[i] == ' ')
    {
        spaces++;
        i++;
    }
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
    return (ft_strndup(str + length + 1 + spaces,  i - length - spaces));
}

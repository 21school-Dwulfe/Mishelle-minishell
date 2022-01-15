#include "../includes/main.h"

void	msh_specials_cut(char **str, int *i, int end)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(*str);
	ft_memset((*str) + *i, '\0', sizeof(char) * end);
	tmp = *str;
	*str = msh_concat_str(*str, len, NULL);
	ft_strdel(&tmp);
	(*i)--;
}

void    msh_specials_replace(char **str, char *insertion, int *start, int len)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	(void)tmp;
	l = ft_strlen(*str);
	ft_memset((*str) + *start, '\0', sizeof(char) * len);
	tmp = *str;
	*str = msh_concat_str(*str, l, insertion);
	ft_strdel(&tmp);
	(*start)--;
}

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

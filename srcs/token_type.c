#include "../includes/main.h"

char	*msh_token_dollar(char *str, int *index, char **value_arg)
{
	int	i;
	char *result;

	i = *index;
	while (str[i]
	&& (str[i] != ' ' || str[i] != ' ' || str[i] != '>'
		|| str[i] != '<' || str[i] != '|' || str[i] != '('))
		i++;
	result = ft_strndup_se(str + *index, i, 0);
	value_arg = NULL;
	return (result);
}

char	*msh_token_quotes(char *str, int *index, char **value_arg)
{
	char *result;

	result = msh_get_str_inside(str + *index, "\'\"", 0);
	value_arg = NULL;
	return (result);
}
char    *msh_curl_braces(char *str, int *index, char **value_arg)
{
	(void)str;
	(void)index;
	(void)value_arg;
	return (NULL);
}

char    *msh_dollar_braces(char *str, int *index, char **value_arg)
{
	(void)str;
	(void)index;
	(void)value_arg;
	return (NULL);
}

char    *msh_dollar(char *str, int *index, char **value_arg)
{
	(void)str;
	(void)index;
	(void)value_arg;
	return (NULL);
}
#include "../includes/main.h"

int msh_validation_redirs(char *str, int *i)
{
	int l[4];
	char *ptr;

	ptr = NULL;
	ft_bzero(l, sizeof(int) * 4);
	l[0] = *i;
	while (str[l[0]] == str[*i] && (l[0] - *i) + 1 < 3)
			l[0]++;
	while (str[l[0]] == ' ')
		l[0]++;
	if (str[l[0]] == '<' && str[l[0] + 1] == '>')
		return (msh_unexpected_token_error(&str[l[0]], 2));
	ptr = ft_strchr("|;<>", str[l[0]]);
	if (ptr)
		l[2] = *ptr;
	if(str[l[0]] == '\0')
		return (msh_unexpected_token_error("newline", 7));
	if (!(ft_abs(l[2] - str[*i]) == 2))
		l[3] = 1;
	l[1] = l[0];
	while (str[l[1]] == l[2] && l[1] + l[3] - l[0] < 3)
		l[1]++;
	if (l[2] && l[2] != 'n')
		return (msh_unexpected_token_error(str + l[0], l[1] - l[0]));
	return (0);
}

int	msh_validate_line(char *line)
{
	int				i;
	unsigned int	ascii[256];

	i = 0;
	ft_bzero(ascii, sizeof(char) * 256);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			ascii[(unsigned char)line[i]]++;
		i++;
	}
	if (ft_strlen(line) == ascii[32])
		return (1);
	return (0);
}

int	msh_validation_pipe(char *str, int *i)
{
	(void)str;
	if (*i == 0)
		return (msh_unexpected_token_error("|", 1));
	return (0);
}

// int	msh_validation_brackets(char *str, int *i)
// {
// 	static int ascii[255];
// 	static char *ascii_i;

// 	if (!ascii_i)

// }

int	msh_validation_closest_chars(char *str, int *i)
{
	// if (str[*i] && (str[*i] == ')' || str[*i] == '('))
	// 	return (msh_validation_brackets(str, i));
	if (str[*i] == '|')
		return (msh_validation_pipe(str, i));
	if (str[*i] == '>' || str[*i] == '<')
		return (msh_validation_redirs(str, i));
	return (0);
}

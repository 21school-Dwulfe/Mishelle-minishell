#include "../includes/main.h"

int msh_conditions_dollar_braces(char *str, int *i)
{
	if (str[*i] == '$' && str[*i] == '(')
		return (DOLLAR_BRACES);
	else
		return (0);
}

int	msh_conditions_redirects(char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] != '>')
		return (REDIRECT);
	if (str[*i] == '<' && str[*i + 1] != '<')
		return (R_REDIRECT);
	if (str[*i] == '>' && str[*i + 1] == '>')
		return (D_REDIRECT);
	if (str[*i] == '<' && str[*i + 1] == '<')
		return (RD_REDIRECT);
	return (0);
}

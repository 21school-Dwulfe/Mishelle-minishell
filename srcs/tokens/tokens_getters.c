#include "minishell.h"

char	*msh_generate_tokens(int specials, int num)
{
	char	*str;
	char	*tmp;
	char	*result;
	size_t	i[2];

	if (DEV_TOKENS)
		str = msh_tokens_pseudo_dev(specials);
	else
		str = msh_tokens_pseudo(specials);
	tmp = ft_itoa(num);
	i[0] = ft_strlen(str);
	i[1] = ft_strlen(tmp);
	result = ft_calloc(i[0] + i[1] + 3, sizeof(char));
	ft_strncat(result, str, i[0]);
	ft_strncat(result, tmp, i[0] + i[1] + 3);
	result[ft_strlen(result)] = '%';
	result[ft_strlen(result)] = ' ';
	ft_strdel(&tmp);
	ft_strdel(&str);
	return (result);
}

t_arg	*msh_get_token_value(t_command *cmd, char *token)
{
	int		stop_int;
	t_arg	*tok;

	if (!token)
		return (NULL);
	stop_int = 0;
	tok = cmd->args_token;
	while (token[stop_int] && !ft_isdigit(token[stop_int])
		&& token[stop_int] != ' ')
		stop_int++;
	if (token[stop_int] == '\0')
		return (NULL);
	while (tok)
	{
		if (tok->order == ft_atoi(token + stop_int))
			break ;
		tok = tok->next;
	}
	return (tok);
}

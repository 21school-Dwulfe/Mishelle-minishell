#include "../includes/main.h"

char	*msh_spec_tokens(int specials, int num)
{
	char	*str;
	char	*tmp;
	char	*result;
	size_t	i[2];

	(void)num;
	if (specials == 12)
		str = " QUOTES";
	else if (specials == 13)
		str = " D_QUOTES";
	else if (specials == 14)
		str = " S_QOUTES";
	else if (specials == 15)
		str = " CURL_BRACES";
	else if (specials == 16)
		str = " DOLLAR_BRACES";
	else if (specials == 17)
		str = " DOLLAR";
	else
		str = (void *)0;
	tmp = ft_itoa(num);
	i[0] = ft_strlen(str);
	i[1] = ft_strlen(tmp);
	result = ft_calloc(i[0] + i[1] + 2, sizeof(char));
	ft_strncat(result, str, i[0]);
	ft_strncat(result, tmp, i[0] + i[1] + 1);
	result[ft_strlen(result)] = ' ';
	result[ft_strlen(result) + 1] = '\0';
	ft_strdel(&tmp);
	return (result); 
}

char	*msh_specify_token(t_command *cmd, int *length, char *str, int specials)
{
	int			l[2];
	char		*value;
	char		**value_arg;

	value_arg = NULL;
	value = g_info.func[specials](str, length, value_arg); 
	msh_add_token(cmd, value, value_arg, specials);
	cmd->args_token->specials = specials;
	l[0] = ft_strlen(str);
	l[1] = ft_strlen(value);
	ft_memset(str + *length, '\0', sizeof(char) * l[1] + 2);
	str = msh_concat_str(str, l[0], msh_spec_tokens(specials, g_info.num_token++));
	return (str);
}

t_arg *msh_get_token_value(t_command *cmd, char *token)
{
	int		stop_int;
	t_arg	*tok;

    stop_int = 0;
	tok = cmd->args_token;
	while (!ft_isdigit(token[stop_int]))
		stop_int++;
	while (tok)
	{
		if (!ft_strncmp(tok->value, token, stop_int))
			break ;
		tok = tok->next;
	}
	return (tok);
}

void	msh_exchange_token_value(t_command *cmd)
{
	int i;
	t_arg	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		tmp = msh_get_token_value(cmd, cmd->args[i]);
		if (tmp)
		{
			ft_strdel(&cmd->args[i]);
			cmd->args[i] = ft_strdup(tmp->value);
		}	
		i++;
	}
	
}

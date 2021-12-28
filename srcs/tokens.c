#include "../includes/main.h"

int	msh_is_token(char *arg)
{

	if (!ft_strncmp(arg, "QUOTES", 6))
		return (1);
	else if (!ft_strncmp(arg, "D_QUOTES", 8))
		return (1);
	else if (!ft_strncmp(arg, "S_QOUTES", 8))
		return (1);
	else if (!ft_strncmp(arg, "CURL_BRACES", 11))
		return (1);
	else if (!ft_strncmp(arg, "DOLLAR_BRACES", 13))
		return (1);
	else if (!ft_strncmp(arg, "DOLLAR", 6))
		return (1);
	else
		return (0);
}

char	*msh_spec_tokens(int specials, int num)
{
	char	*str;
	char	*tmp;
	char	*result;
	size_t	i[2];

	(void)num;
	if (specials == 12)
		str = " S_QOUTES";
	else if (specials == 13)
		str = " QUOTES";
	else if (specials == 14)
		str = " D_QUOTES";
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
	char		*tmp[2];
	char		*value;
	char		**value_arg;
	t_arg		*arg;

	value_arg = NULL;
	value = g_info.func[specials](str, length, value_arg);
	arg = msh_add_token(cmd, value, value_arg, specials);
	arg->order = g_info.num_token++;
	l[1] = ft_strlen(value);
	if (ft_strchr(arg->value, '$'))
	{
		if (specials != QUOTES)
			msh_evaluate_env_call_if_exist(&arg->value, g_info.env);
	}
	l[0] = ft_strlen(str);
	ft_memset(str + *length, '\0', sizeof(char) * l[1] + 2);
	tmp[0] = msh_spec_tokens(specials, arg->order);
	tmp[1] = msh_concat_str(str, l[0], tmp[0]);
	ft_strdel(&tmp[0]);
	return (tmp[1]);
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
		if (tok->order == ft_atoi(token + stop_int))
			break ;
		tok = tok->next;
	}
	return (tok);
}

void	msh_exchange_token_value(t_command *cmd, int index)
{
	t_arg *tmp;

	tmp = msh_get_token_value(cmd, cmd->args[index]);
	ft_strdel(&cmd->args[index]);
	cmd->args[index] = ft_strdup(tmp->value);
}

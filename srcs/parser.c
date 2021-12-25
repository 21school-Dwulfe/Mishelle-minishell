#include "../includes/main.h"
#include <string.h>

// parse string until occurs special or stop signs( ; | & > >> < << <& <<& \n)
// validation operators order
// validation cmd names
// validation cmd args

int	msh_multiple_iterator(int num, int *i, int sign)
{
	int in;

	in = 0;
	while (in < num)
	{
		if (sign > -1)
			(*i)++;
		else
			(*i)--;
		in++;
	}
	return (in);
}
int	msh_validation_closest_chars(char *str, int *i, int *specials)
{
	if (str[*i] && str[*i + 1] == ')')
		return (*specials == ERROR);
	if ((str[*i] == '>' || str[*i] == '<') && str[*i + 1] == '|')
		return (*specials == ERROR);
	if (str[*i] == ';' && str[*i + 1] == '|')
		return (*specials == ERROR);
	else
		return (0);
}

int	msh_check_special_signs(char *str, int *i, int *specials)
{
	if (msh_validation_closest_chars(str, i, specials))
		return (*specials = ERROR);
	if ((ft_strnstr(str + *i, "\";\"", 3) || ft_strnstr(str + *i, "\';\'", 3))
		&& msh_multiple_iterator(3, i, 1))
		return (*specials = 0);
	if (str[*i] == '\'' && str[*i + 1] == '\'')
		return (!(str = ft_memset(str + *i++, '\0', sizeof(char) * 2)));
	if (str[*i] == '\"' && str[*i + 1] == '\"')
		return (!(str = ft_memset(str + *i++, '\0', sizeof(char) * 2)));
	if (str[*i] == '\'' && str[*i + 1] != '\'')
		return (*specials = QUOTES);
	if (str[*i] == '\"' && str[*i + 1] != '\"')
		return (*specials = D_QUOTES);
	if (str[*i] == '$' && str[*i] != '(')
		return (*specials = DOLLAR);
	if (*i > 0 && str[*i] == ';')
		return (*specials = SEMICOLON);
	if (str[*i] == '|')
		return (*specials = PIPE);
	if (str[*i + 1] == '\0' && ++*i)
		return (*specials = 1);
	return (*specials = 0);
}

t_arg *msh_create_token(char *value, char **value_arr, int order)
{
	t_arg 	*args_token;

	args_token = malloc(sizeof(t_arg));
	args_token->value = value;
	args_token->value_arr = value_arr;
	if (order < 0)
		args_token->order = order;
	else
		args_token->order = 0;
	return (args_token);
}

void	msh_add_token(t_command *cmd, char *value, char **value_arr, int order)
{
	t_arg	*tmp;

	if (cmd && !cmd->args_token)
	{
		cmd->args_token = msh_create_token(value, value_arr, order);
		cmd->args_token->prev = cmd->args_token;
	}
	else
	{
		tmp = msh_create_token(value, value_arr, order);
		cmd->args_token->prev->next = tmp;
		tmp->prev = cmd->args_token->prev;
		cmd->args_token->prev = tmp;
	}
}

// char *msh_get_token_value(char *token, int num)
// {

// }

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

char	*msh_token_qoutes(char *str, int *index, char **value_arg)
{
	char *result;

	result = msh_get_str_inside(str + *index, "\'\"", 0);
	value_arg = NULL;
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

void	msh_parse(char *str)
{
	t_command	*cmd;
	int			mem;
	int			length;
	char		*tmp;
	int			specials;

	mem = 0;
	length = 0;
	specials = 0;
	cmd = msh_create_command((void *)0);
	cmd->prev = cmd;
	while (str[length])
	{
		if (specials > 0)
			mem = length;
		msh_check_special_signs(str, &length, &specials);
		if (specials > 0)
		{
			if (specials >= 12)
				str = msh_specify_token(cmd, &length, str, specials);
			if (specials < 3 || str[length] == '\0')
			{
				tmp = ft_strndup(str + mem, length - mem);
				if (cmd->args)
					msh_add_command(&cmd, ft_split_se(tmp, ' '));
				else
					cmd->args = ft_split_se(tmp, ' ');
				cmd->num_args = ft_str_count(cmd->args);
				msh_evaluate_env_call_if_exist(cmd, g_info.env);
				if (specials == PIPE)
					cmd->piped++;
				g_info.num_of_commands++;
				ft_strdel(&tmp);
			}
			if (specials >= 12)
				specials = 0;
		}
		length++;
	}
	g_info.cur_cmd = cmd;
	msh_common_parse();
}

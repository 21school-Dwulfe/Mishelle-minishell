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
	{
		ft_memset(str + *i, ' ', sizeof(char) * 2);
		(*i)++;
		return (!(str = ft_memset(str + *i, ' ', sizeof(char) * 2)));
	}
	if (str[*i] == '\"' && str[*i + 1] == '\"')
	{
		ft_memset(str + *i, ' ', sizeof(char) * 2);
		(*i)++;
		return (0);
	}
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

int	msh_parse(char *str)
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
			if (specials > 12)
				str = msh_specify_token(cmd, &length, str, specials);
			if (specials < 3 || str[length] == '\0')
			{
				tmp = ft_strndup(str + mem, length - mem);
				if (cmd->args)
					msh_add_command(&cmd, ft_split_se(tmp, ' '));
				else
					cmd->args = ft_split_se(tmp, ' ');
				cmd->num_args = ft_str_count(cmd->args);
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
	if (g_info.num_token)
		ft_strdel(&str);
	g_info.cur_cmd = cmd;
	return(msh_common_parse());
}

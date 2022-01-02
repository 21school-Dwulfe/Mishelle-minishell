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

void	msh_side_effects(char *str, int *i, int *specials)
{
	(void)specials;
	if (str[*i] == '\'' && str[*i + 1] == '\'')
	{
		ft_memset(str + *i, ' ', sizeof(char) * 2);
		(*i)++;
	}
	if (str[*i] == '\"' && str[*i + 1] == '\"')
	{
		ft_memset(str + *i, ' ', sizeof(char) * 2);
		(*i)++;
	}
}

int	msh_check_special_signs(char *str, int *i, int *specials)
{
	if (msh_validation_closest_chars(str, i))
		return (*specials = ERROR);
	msh_side_effects(str, i, specials);
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
		return (*specials = -1);
	return (*specials = 0);
}

int	msh_parse(char *str)
{
	t_command	*cmd;
	int			mem;
	int			length;
	int			specials;
	char		*tmp;

	mem = 0;
	length = 0;
	specials = 0;
	cmd = msh_create_command((void *)0);
	cmd->prev = cmd;
	g_info.cur_cmd = cmd;
	while (str[length])
	{
		if (specials > 0)
			mem = length;
		if(msh_check_special_signs(str, &length, &specials) == ERROR)
			return (-1);
		if (specials > 12)
				str = msh_specify_token(cmd, &length, str, specials);
		if (specials != 0 && specials < 3)
		{
			tmp = ft_strndup(str + mem, length - mem);
			if (cmd->args)
				msh_add_command(&cmd, ft_split(tmp, ' '));
			else
				cmd->args = ft_split(tmp, ' ');
			cmd->num_args = ft_str_count(cmd->args);
			cmd->specials = specials;
			if (specials == PIPE)
				cmd->piped++;
			g_info.num_of_commands++;
			ft_strdel(&tmp);
		}
		if (specials >= 12)
			specials = 0;
		length++;
	}
	if (g_info.num_token)
		ft_strdel(&str);
	return(0);
}

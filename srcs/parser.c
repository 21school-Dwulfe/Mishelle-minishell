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

static void	msh_save_command(t_command *cmd, char *str, int *i)
{
	char		*tmp;

	tmp = ft_strndup(str + i[0], i[1] - i[0]);
	if (cmd->args)
		msh_add_command(&cmd, ft_split(tmp, ' '));
	else
		cmd->args = ft_split(tmp, ' ');
	cmd->num_args = ft_str_count(cmd->args);
	cmd->specials = i[2];
	if (i[2] == PIPE)
		cmd->piped++;
	g_info.num_of_commands++;
	ft_strdel(&tmp);
}

int	msh_parse(char *str)
{
	t_command	*cmd;
	int			i[3];

	
	ft_bzero(i, sizeof(int) * 3);
	cmd = msh_create_command((void *)0);
	cmd->prev = cmd;
	g_info.cur_cmd = cmd;
	while (str[i[1]])
	{
		if (i[2] > 0)
			i[0] = i[1];
		if(msh_check_special_signs(str, &i[1], &i[2]) == ERROR)
			return (-1);
		if (i[2] > 12)
			str = msh_specify_token(cmd, &i[1], str, i[2]);
		if (i[2] != 0 && i[2] < 3)
			msh_save_command(cmd, str, i);
		if (i[2] >= 12)
			i[2] = 0;
		i[1]++;
	}
	if (g_info.num_token)
		ft_strdel(&str);
	return(0);
}

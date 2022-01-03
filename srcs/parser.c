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

void	msh_side_effects(char **str, int *i, int *specials)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	if (*specials == 22 || *specials == 23)
	{
		len = ft_strlen(*str);
		ft_memset((*str) + *i, '\0', sizeof(char) * 2);
		tmp = *str;
		*str = msh_concat_str(*str, len, NULL);
		ft_strdel(&tmp);
		(*i)--;
	}
}

int	msh_check_special_signs(char *str, int *i, int *specials)
{
	if (msh_validation_closest_chars(str, i))
		return (*specials = ERROR);
	if (str[*i] == '\"' && str[*i + 1] == '\"')
		return (*specials = 22);
	if (str[*i] == '\'' && str[*i + 1] == '\'')
		return (*specials = 23);
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
		if (msh_check_special_signs(str, &i[1], &i[2]) == ERROR)
			return (-1);
		if (i[2] == 22 || i[2] == 23)
			msh_side_effects(&str, &i[1], &i[2]);
		if (i[2] > 12 && i[2] < 20)
			str = msh_specify_token(cmd, &i[1], str, i[2]);
		if (i[2] != 0 && i[2] < 3)
			msh_save_command(cmd, str, i);
		if (i[2] >= 12 && i[2] < 20)
			i[2] = 0;
		i[1]++;
	}
	if (g_info.num_token)
		ft_strdel(&str);
	return(0);
}

#include "../includes/main.h"

// parse string until occurs special or stop signs( ; | & > >> < << <& <<& \n)
// validation operators order
// validation cmd names
// validation cmd args



int	msh_multiple_iterator(int num, int *i)
{
	int in;

	in = 0;
	while (in < num)
	{
		in++;
		(*i)++;
	}
	return (in);
}

int	msh_check_special_signs(char *str, int *i, int *specials)
{
	if ((ft_strnstr(str + *i, "\";\"", 3) || ft_strnstr(str + *i, "\';\'", 3))
		&& msh_multiple_iterator(3, i))
		return (*specials = 0);
	if (*i > 0 && str[*i] == ';')
		return (*specials = SEMICOLON);
	if (str[*i + 1] == '\0' && msh_multiple_iterator(2, i))
		return (*specials = 1);
	if (str[*i] == '|')
		return (*specials = PIPE);
	return (*specials = 0);
}

void	msh_parse(char *str)
{
	int			mem;
	int			length;
	char		*tmp;
	int			specials;

	mem = 0;
	length = 0;
	specials = 0;
	while (str[length])
	{
		if (specials > 0)
			mem = length;
		msh_check_special_signs(str, &length, &specials);
		if (specials > 0)
		{
			tmp = ft_strndup(str + mem, length - mem);
			msh_add_command(&g_info.cur_cmd, msh_split(tmp, ' '));
			if (specials == PIPE)
				g_info.cur_cmd->piped++;
			msh_evaluate_env_call_if_exist(g_info.cur_cmd, g_info.env);
			g_info.num_of_commands++;
			ft_strdel(&tmp);
		}
		length++;
	}
	msh_common_parse();
}
	// int i = 0;
	// t_command *t = g_info.current_command;
	// while (t)
	// {
	// 	while (t->args[i])
	// 	{
	// 		printf("%s\n",t->args[i]);
	// 		i++;
	// 	}
	// 	t = t->next;
	// }
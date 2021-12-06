#include "../includes/main.h"

// parse string until occurs special or stop signs( ; | & > >> < << <& <<& \n)
// validation operators order
// validation cmd names
// validation cmd args

int	msh_set_specials(char *str, int *length, int specials)
{
	return (g_info.func[specials](str, length));
}

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
	if (str[*i] == '|')
		return (*specials = PIPE);
	
	if (str[*i] == '&')
		return (*specials = AMPERSAND);
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
		mem = length;
		while (str[length])
		{
			msh_check_special_signs(str, &length, &specials);
			if (specials > 0)
				break ;
			length++;
		}
		tmp = ft_strndup(str + mem, length - mem);
		msh_add_command(&g_info.cur_cmd, msh_split(tmp, ' '));
		msh_evaluate_env_call_if_exist(g_info.cur_cmd, g_info.env);
		g_info.cur_cmd->num_args = ft_str_count(g_info.cur_cmd->args);
		g_info.num_of_commands++;
		ft_strdel(&tmp);
		if (msh_set_specials(str, &length, specials) == -1)
			return ;
	}
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
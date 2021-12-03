#include "../includes/main.h"

// parse string until occurs special or stop signs( ; | & > >> < << <& <<& \n)
// validation operators order
// validation cmd names
// validation cmd args

void	msh_set_specials(char *str, int *length, int specials)
{
	if (str && specials)
		g_info.func[specials](str, length);
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
	if (ft_strnstr(str + *i, ">>", 3))
		return (*specials = D_REDIRECT);
	if (ft_strnstr(str + *i, "<<", 3))
		return (*specials = RD_REDIRECT);
	if (str[*i] == '>')
		return (*specials = REDIRECT);
	if (*i > 0 && str[*i] == '<')
		return (*specials = R_REDIRECT);
	if (str[*i] == '&')
		return (*specials = AMPERSAND);
	return (*specials = 0);
}

int	ft_str_count(char **str)
{
	int i;
	char *tmp;

	i = 0;
	while (str[i])
	{
		tmp = str[i];
		i++;
	}
	return (i);
}

void	msh_parse(char *str)
{
	int			mem;
	int			length;
	char		*tmp;
	int			specials;
	t_command	*cur_cmd;

	mem = 0;
	length = 0;
	specials = 0;
	cur_cmd = msh_create_command(NULL); 
	g_info.current_command;
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
		
		// if (specials > 3 && specials < 7)
		// {
		// 	if (cmd-> != NULL)
		// 		msh_add_redirect();
		// }
		// else if ()
		msh_add_command(cur_cmd, msh_split(tmp, ' '));
		g_info.current_command->number_args = ft_str_count(g_info.current_command->args);
		g_info.num_of_commands++;
		ft_delptr(tmp);
		msh_set_specials(str, &length, specials);
		length++;
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
#include "../includes/main.h"

// parse string until occurs special or stop signs( ; | & > >> < << <& <<& \n)
// validation operators order
// validation cmd names
// validation cmd args

// void	msh_set_specials(char *str, int *length, int specials)
// {
// 	if (specials == 4 || specials == 3)
// 	{
		
// 	}
	
// }

int	msh_check_special_signs(char *c, int i)
{
	int specials;

	specials = 0;
	if (i > 0 && c[i] == ';' )
		specials = 1;
	if (*c == '|')
		specials = 2;
	if (*c == '>')
		specials = 3;
	if (i > 0 && *c == '<')
		specials = 4;
	if (*c == '&')
		specials = 5;
	if (ft_strnstr(c + i, ">>", 3))
		specials = 6;
	if (ft_strnstr(c + i, "<<", 3))
		specials = 7;
	//g_info.func[specials](c, i);
	return (specials);
}

int	ft_str_count(char **str)
{
	int i;
	char *tmp;


	i = 0;
	//printf("%s", str[i]);
	while (str[i])
	{

		tmp = str[i];
		i++;
	}
	return (i);
}

void	msh_parse(char *str)
{
	int		mem;
	int		length;
	char	*tmp;
	//char	*c;

	mem = 0;
	length = 0;
	while (str[length])
	{
		mem = length;
		while (str[length] && !msh_check_special_signs(str, length))
			length++;
		tmp = ft_strndup(str + mem, length - mem);
		msh_add_command(&g_info.current_command, msh_split(tmp, ' '));
		// c = ft_strrchr(tmp, ';');
		// if (c && ft_strlen(tmp) > 1)
		// 	c = \0';
		g_info.current_command->number_args = ft_str_count(g_info.current_command->args);
		g_info.num_of_commands++;
		ft_delptr(tmp);
	//	msh_set_specials(str, &length, msh_check_special_signs(str, length));
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
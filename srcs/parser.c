#include "../includes/main.h"

// parse string until occurs special or stop signs( ; | & > >> < << <& <<& \n)
// validation operators order
// validation cmd names
// validation cmd args

void	msh_set_specials(char *str, int *length, int specials)
{
	if (specials == 4 || specials == 3)
	{
		if (ft_strnstr(str + *length, ">> ", 3))
			specials = 5;
		if (ft_strnstr(str + *length, "<< ", 3))
			specials = 6;
	}
	g_info.func[specials](str, length);
}

int	msh_check_special_signs(char c)
{
	if (c == ';')
		return (0);
	if (c == '|')
		return (1);
	if (c == '>')
		return (2);
	if (c == '<')
		return (3);
	if (c == '&')
		return (4);
	return (0);
}

void	msh_parse(char *str)
{
	int		mem;
	int		length;
	char	*tmp;
	(void)str;
	mem = 0;
	length = 0;
	while (str[length])
	{
		mem = length;
		while (str[length] && !msh_check_special_signs(str[length]))
			length++;
		tmp = ft_substr(str, mem, length);
		msh_add_command(&g_info.current_command, msh_split(tmp, ' '));
		g_info.num_of_commands++;
		ft_delptr(tmp);

		msh_set_specials(str, &length, msh_check_special_signs(str[length]));
		length++;
	}
}
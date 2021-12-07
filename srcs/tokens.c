#include "../includes/main.h"

int msh_check_specials(char *str, int *i)
{

	if (str[*i] == ';' )//|| str[*i] == ' ')
		return (1);
	if (str[*i] == '|')
		return (2);
	return (0);
}


void    msh_tokenization(char *str)
{
	(void)str;
	// int     mem;
	// int     index;
	// char    *tmp;
	// int     specials;

	// index = 0;
	// g_info.cur_cmd =  msh_create_command(NULL);
	// while (str[index])
	// {
	// 	mem = index;
	// 	g_info.scenario[specials](str, &index);
	// }
}
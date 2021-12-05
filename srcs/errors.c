#include "../includes/main.h"

void	msh_error(char *str, char *message, char *token_str, int token_len)
{
	int i;

	i = 0;
	(void)str;
	while (message[i])
		i++;
	write(2, message, i);
	write(2, " `", 2);
	write(2, token_str, token_len);
	write(2, "'", 1);
	msh_struct_clear();
	exit(1);
}

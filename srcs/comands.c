#include "../includes/main.h"

void	msh_print_dir_(void)
{
	char str[512];

	getcwd(str, sizeof(str));
	printf("%s ", str);
}
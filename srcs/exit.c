#include "../includes/main.h"

int	msh_read_error_code(void)
{
	return (g_info.exit_code);
}

void	msh_save_error_code(int code)
{
	g_info.exit_code = code;
}
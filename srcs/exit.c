#include "../includes/main.h"

int	msh_read_error_code(void)
{
    int res;
    
    res = g_info.exit_code;
	return (res);
}

void	msh_save_error_code(int code)
{
	g_info.exit_code = code;
}
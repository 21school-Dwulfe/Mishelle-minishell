#include "../../includes/main.h"

int	msh_custom_pwd(t_command *cmd)
{
	char *str;

	(void)cmd;
	str = NULL;
	str = getcwd(NULL, 0);
	ft_putendl_fd(str, 1);
	ft_strdel(&str);
	msh_save_error_code(0);
	return (1);
}
#include "../../includes/main.h"

int	msh_custom_env(t_command *cmd)
{
	int i;

	i = 0;
	(void)cmd;
	while (g_info.env[i])
	{
		if (ft_index_of(g_info.env[i], '=', 0) != -1)
			ft_putendl_fd(g_info.env[i], 1);
		i++;
	}
	msh_save_error_code(0);
	return (1);
}
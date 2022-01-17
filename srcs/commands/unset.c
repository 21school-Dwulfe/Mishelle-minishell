#include "../../includes/main.h"

int	msh_custom_unset(t_command *cmd)
{
	int		i;
	int		res;
	char	**args;
	char	**tmp;
	int		length;

	i = 0;
	args = cmd->args;
	length = ft_str_count(g_info.env);
	while (args[i])
	{
		res = msh_env_exist(g_info.env, args[i]);
		if (res > -1)
		{
			ft_strdel(&g_info.env[res]);
			tmp = msh_concat_args(g_info.env, length);
			if (!tmp)
				return (msh_perror("malloc"));
			free(g_info.env);
			g_info.env = tmp;
			length = ft_str_count(g_info.env);
		}
		i++;
	}
	msh_save_error_code(0);
	return (1);
}

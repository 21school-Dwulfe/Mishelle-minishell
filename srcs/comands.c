#include "../includes/main.h"

int	msh_custom_pwd(t_command *cmd)
{
	char *str;

	str = NULL;
	(void)cmd;
	str = getcwd(str, sizeof(str) * 512);
	ft_putendl_fd(str, 1);
	ft_strdel(&str);
	g_info.exit_code = 0;
	return (1);
}

int	msh_custom_echo(t_command *cmd)
{
	short	is_nl;
	int		len;
	int		l[4];
	char	*tmp[4];

	is_nl = 1;
	len = 1;
	ft_bzero(l, sizeof(int) * 4);
	ft_bzero(tmp, sizeof(char *) * 4);
	tmp[0] = ft_strchr(cmd->args[1], '-');
	if (tmp[0] && *(tmp[0] + 1) == 'n' && (--is_nl == 0))
			len = 2;
	if (cmd->num_args > 1 && !(len == 2 && cmd->num_args == 2))
	{
		l[2] = len;
		while (l[2] < cmd->num_args)
			l[0] += ft_strlen(cmd->args[l[2]++]);
		tmp[1] = ft_calloc(sizeof(char), (l[0] + cmd->num_args - 2));
		while (len < cmd->num_args)
		{
			l[1] = (int)ft_strlcat(tmp[1], cmd->args[len], (l[0] + cmd->num_args - 1));
			if (len != cmd->num_args - 1)
				tmp[1][l[1]] = ' ';
			len++;
		}
		ft_putstr_fd(tmp[1], 1);
		ft_strdel(&tmp[1]);
	}
	if (is_nl)
		ft_putstr_fd("\n", 1);
	g_info.exit_code = 0;
	return (1);
}

int	msh_custom_env(t_command *cmd)
{
	int i;

	i = 0;
	(void)cmd;
	while (g_info.env[i])
	{
		if (ft_index_of(g_info.env[i], '=') != -1)
			ft_putendl_fd(g_info.env[i], 1);
		i++;
	}
	g_info.exit_code = 0;
	return (1);
}

int	msh_custom_unset(t_command *cmd)
{
	int		i;
	int		res;
	char	**args;
	int		length;

	i = 0;
	args = cmd->args;
	length = ft_str_count(g_info.env);
	while (args[i])
	{
		res = msh_env_exist(g_info.env, args[i]);
		if (res > -1)
			ft_strdel(&g_info.env[res]);
		i++;
	}
	g_info.env = msh_concat_args(g_info.env, length);
	return (1);
}

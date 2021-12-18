#include "../includes/main.h"

char	*msh_get_path(char *cmd_name, char **env)
{
	int		i[2];
	char	*tmp[4];
	char	*path;
	char	**splited;

	ft_bzero(i, sizeof(int) * 2);
	path = msh_get_if_exist(env, "PATH");
	splited = ft_split(path, ':');
	if (access(cmd_name, X_OK) == -1 && i[1]++)
		while (splited[i[0]])
		{
			tmp[0] = ft_strjoin(splited[i[0]], "/");
			tmp[1] = ft_strjoin(tmp[0], cmd_name);
			ft_strdel(&tmp[0]);
			if (access(tmp[1], F_OK) == 0 
				&& !ft_arrstr_del(splited, ft_str_count(splited)))
					return (tmp[1]);
			else
				ft_strdel(&tmp[1]);
			i[0]++;
		}
	return (NULL);
}

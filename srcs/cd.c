#include "../includes/main.h"

int	msh_cd_validation(t_command *cmd)
{
	if (cmd->num_args > 1)
	{
		DIR *dir = opendir(cmd->args[1]);
		if (dir == NULL)
			return (msh_perror(cmd->args[1]));
		else
			if (closedir(dir))
				msh_perror(cmd->args[1]);
		if (cmd->args[1][0] == '.' 
			&& cmd->args[1][1] == '\0')
			return (1);
	}
	return (0);
}

int	msh_custom_cd(t_command *cmd)
{
	char	str[512];
	char	*env_value[4];

	if (msh_cd_validation(cmd))
		return (1);
	ft_bzero(env_value, sizeof(char *) * 4);
	if (cmd->num_args == 1)
		env_value[1] = msh_env_get_if_exist(g_info.env, "HOME");
	else
		env_value[1] = cmd->args[1];
	env_value[0] = msh_env_get_if_exist(g_info.env, "OLDPWD");
	env_value[2] = msh_env_get_if_exist(g_info.env, "PWD");
	if (ft_strcmp(env_value[0], env_value[2]) == 0)
	{
        env_value[4] = ft_strrchr(env_value[0], '/');
        if (env_value[4] != NULL && &env_value[0] - &env_value[4] != 0)
		    env_value[0] = ft_strndup(env_value[0], *env_value[4]);
        else if ()
        {
            
        }
        else
            env_value[0] = ft_strdup("/");
	}
	getcwd(str, sizeof(str));
	if (cmd->num_args > 1 && !ft_strncmp(cmd->args[1], "..", 3))
		env_value[3] = ft_strdup(str);
	else
	{
		env_value[3] = env_value[2];
		env_value[1] = env_value[0]; 
	}
	msh_modify_env_var(&g_info.env[msh_env_str(g_info.env, "OLDPWD")], env_value[3]);
	msh_modify_env_var(&g_info.env[msh_env_str(g_info.env, "PWD")], env_value[1]);
	if(chdir(cmd->args[0]) == -1)
		msh_perror("cd");
	return (1);
}

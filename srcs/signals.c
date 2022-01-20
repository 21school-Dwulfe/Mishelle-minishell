#include "../includes/main.h"

void	msh_child_sig(int sig)
{
	if (sig == SIGINT)
	{
		exit(2);
	}
	if (sig == SIGQUIT)
	{
		exit(3);
	}
}


void	msh_pipex_sig(int sig)
{
	// char *shlvl;
	
	// shlvl = msh_get_env_by_key(g_info.env, "SHLVL");
	// if (ft_atoi(shlvl) == 2)
	// {
		if (sig == SIGINT)
		{
			write(2, "\n", 2);
		}
		if (sig == SIGQUIT)
			write(2, "Quit: 3\n", 8);
//	}
}

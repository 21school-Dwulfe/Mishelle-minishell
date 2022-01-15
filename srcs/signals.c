#include "../includes/main.h"

void	msh_child_sig(int sig)
{
	if (sig == SIGINT)
		exit(2);
	if (sig == SIGQUIT)
		exit(3);
}

void	msh_pipex_sig(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
	if (sig == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}
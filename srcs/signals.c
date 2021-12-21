#include "../includes/main.h"

void msh_sigint_handler(int sig_num)
{
	(void)sig_num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void msh_signal_child(int sig)
{
	(void)sig;
	signal(SIGINT, msh_sigint_handler);
}

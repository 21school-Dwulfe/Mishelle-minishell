#include "../includes/main.h"

void	msh_init_global_cmd()
{
	t_command	*cmd;
	
	cmd = msh_create_command((void *)0);
	cmd->prev = cmd;
	g_info.cur_cmd = cmd;
}

t_command	*msh_last_cmd(void)
{
    return (g_info.cur_cmd->prev);
}

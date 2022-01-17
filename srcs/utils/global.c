#include "../../includes/main.h"

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

void	msh_struct_clear()
{
	t_command 	*cmd;
	t_redirect	*tmp_red;

	cmd = g_info.cur_cmd;
	g_info.num_token = 0;
	g_info.num_of_commands = 0;
	while (cmd)
	{
		if (cmd->args)
			ft_arrstr_del(cmd->args, ft_str_count(cmd->args));
		msh_clear_tokens(cmd);
		tmp_red = cmd->redirects;
		while (tmp_red)
		{
			cmd->redirects = cmd->redirects->next;
			ft_strdel(&tmp_red->file);
			free(tmp_red);
			tmp_red = cmd->redirects;
		}
		cmd = cmd->next;
		free(g_info.cur_cmd);
		g_info.cur_cmd = NULL;
		g_info.cur_cmd = cmd;
	}
}

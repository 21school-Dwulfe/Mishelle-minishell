#include "../includes/main.h"

t_command	*msh_create_command(char	**dstr)
{
	t_command	*cmd;	

	cmd = malloc(sizeof(t_command));
	cmd->args = dstr;
	cmd->background = 0;
	cmd->input_file = NULL;
	cmd->out_file = NULL;
	cmd->err_file = NULL;
	cmd->piped = 0;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->number_args = 0;
	return (cmd);
}

void	msh_add_command(t_command **cur_cmd, char **value)
{
	t_command	*tmp;

	tmp = msh_create_command(value);
	if (cur_cmd && *cur_cmd)
	{
		tmp->next = *cur_cmd;
		if ((*cur_cmd)->prev != NULL)
			tmp->prev = (*cur_cmd)->prev;
		else
			tmp->prev = *cur_cmd;
	}
	*cur_cmd = tmp;
}

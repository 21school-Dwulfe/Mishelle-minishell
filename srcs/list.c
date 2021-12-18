#include "../includes/main.h"

t_command	*msh_create_command(char	**dstr)
{
	t_command	*cmd;	

	cmd = malloc(sizeof(t_command));
	cmd->args = dstr;
	cmd->background = 0;
	cmd->input = NULL;
	cmd->out = NULL;
	cmd->err = NULL;
	cmd->piped = 0;
	cmd->build = 0;
	cmd->num_args = ft_str_count(dstr);
	cmd->prev = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redirect	*msh_create_redirect(char *filepath, t_specials specials)
{
	t_redirect *redirect;

	redirect = malloc(sizeof(t_redirect));
	redirect->file = filepath;
	redirect->specials = specials;
	redirect->next = NULL;
	redirect->prev = NULL;
	return (redirect);
}

void	msh_add_command(t_command **cur_cmd, char **value)
{
	t_command	*tmp;

	tmp = msh_create_command(value);
	if (cur_cmd && *cur_cmd)
	{
		(*cur_cmd)->prev->next = tmp;
		tmp->prev = (*cur_cmd)->prev;
		(*cur_cmd)->prev = tmp;
	}
	else
	{
		*cur_cmd = tmp;
		(*cur_cmd)->prev = tmp;
	}
}

void msh_add_redirect(t_redirect **current, char *value, t_specials specials)
{
	t_redirect	*tmp;

	tmp = msh_create_redirect(value, specials);
	if (current && *current)
	{
		(*current)->prev->next = tmp;
		tmp->prev = (*current)->prev;
		(*current)->prev = tmp;
	}
	else
	{
		*current = tmp;
		(*current)->prev = tmp;
	}
}

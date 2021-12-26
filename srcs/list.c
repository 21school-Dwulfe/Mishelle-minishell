#include "../includes/main.h"

void	msh_add_command(t_command **cur_cmd, char **value)
{
	t_command	*tmp;

	if (cur_cmd && *cur_cmd)
	{
		tmp = msh_create_command(value);
		(*cur_cmd)->prev->next = tmp;
		tmp->prev = (*cur_cmd)->prev;
		(*cur_cmd)->prev = tmp;
	}
}

void	msh_push_command(t_command **cur_cmd, char **value)
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

void	msh_add_redirect(t_redirect **current, char *value, t_specials specials)
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

void	msh_add_token(t_command *cmd, char *value, char **value_arr, int order)
{
	t_arg	*tmp;

	if (cmd && !cmd->args_token)
	{
		cmd->args_token = msh_create_token(value, value_arr, order);
		cmd->args_token->prev = cmd->args_token;
	}
	else
	{
		tmp = msh_create_token(value, value_arr, order);
		cmd->args_token->prev->next = tmp;
		tmp->prev = cmd->args_token->prev;
		cmd->args_token->prev = tmp;
	}
}

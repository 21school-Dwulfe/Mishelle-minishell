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
	cmd->args_token = NULL;
	cmd->build = 0;
	if (dstr)
		cmd->num_args = ft_str_count(dstr);
	else
		cmd->num_args = 0;
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

t_arg *msh_create_token(char *value, char **value_arr, int order)
{
	t_arg 	*args_token;

	args_token = malloc(sizeof(t_arg));
	args_token->next = NULL;
	args_token->prev = NULL;
	args_token->value = value;
	args_token->value_arr = value_arr;
	if (order < 0)
		args_token->order = order;
	else
		args_token->order = 0;
	return (args_token);
}

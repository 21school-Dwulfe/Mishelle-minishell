/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_preparings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:06:03 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/19 18:20:30 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int msh_recursion_eval(int i, t_command *cmd, char **buff)
{
	t_arg 	*an_tok;
	char 	*tmp[2];

	an_tok = NULL;
	if (msh_is_token(cmd->args[i]))
	{
		an_tok = msh_get_token_value(cmd, cmd->args[i]);
		if (an_tok)
			tmp[1] = an_tok->value;
		else
			tmp[1] = "";
	}
	else
		tmp[1] = cmd->args[i];
	tmp[0] = ft_strjoin(*buff, tmp[1]);
	ft_strdel(buff);
	ft_strdel(&cmd->args[i]);
	if (cmd->args[i + 1] == NULL || (an_tok && !an_tok->is_prefix))
		cmd->args[i] = tmp[0];
	else if (an_tok && an_tok->is_prefix)
		return(msh_recursion_eval(i + 1, cmd, &tmp[0]));
	return (i);
}


void msh_heredoc_input(char *name)
{
	int 	i[3];
	char	*ptr[3];
	int		fd;
	
	i[0] = ft_strlen(name);
	i[1] = 1;
	rl_clear_history();
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	while (i[1])
	{
		msh_readline(">", &ptr[0]);
		ptr[2] = ft_strnstr(ptr[0], name, i[0]);
		if (ptr[2])
		{
			i[1] = 0;
			ft_strdel(&ptr[0]);
			break ;
		}
		else
		{
			write(fd, ptr[0], ft_strlen(ptr[0]));
			write(fd, "\n", 1);
			ft_strdel(&ptr[0]);
		}
	}
	close(fd);
}

// void msh_heredoc_input(t_arg *tok)
// {
// 	int 	i[3];
// 	char	*ptr[3];
// 	int		fd;
	
// 	i[0] = ft_strlen(tok->name);
// 	i[1] = 1;
// 	rl_clear_history();
// 	fd = open(tok->name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
// 	while (i[1])
// 	{
// 		msh_readline(">", &ptr[0]);
// 		ptr[2] = ft_strnstr(ptr[0], tok->name, i[0]);
// 		i[2] = ft_strlen(tok->value) + ft_strlen(ptr[0]) + 2;
// 		if (ptr[2])
// 		{
// 			i[1] = 0;
// 			ft_strdel(&ptr[0]);
			
// 			break ;
// 		}
// 		else
// 		{
// 			write(fd, ptr[0], ft_strlen(ptr[0]));
// 			write(fd, "\n", 1);
// 		}
// 	}
// }


// i[2] = ft_strlen(tok->value) + ft_strlen(ptr[0]) + 2;
// if (ptr[2])
// {
// 	i[1] = 0;
// 	ft_strdel(&ptr[0]);
// 	break ;
// }
// else
// {
// 	tok->value = ft_realloc(tok->value, i[2]);
// 	tok->value = ft_strncat(tok->value, ptr[0], i[2]);
// 	tok->value[i[2]] = '\n';
// 	ft_strdel(&ptr[0]);
// }
void	msh_token_mutations(t_arg *tok)
{
	if (tok->specials == SLASH)
	{
		tok->value[0] = tok->value[1];
		tok->value[1] = '\0';
	}
	// if (tok->specials == RD_REDIRECT)
	// {
		
	// 	msh_heredoc_input(tok);
	// 	//msh_create_redirect(tok->arg)
	// }
	if (ft_strncmp(tok->name, "$?", 3) == 0)
	{
		ft_strdel(&tok->value);
		tok->value = ft_itoa(msh_read_error_code());
	}
}

void msh_evaluate_all_tokens(t_command *cmd)
{
	int		i;
	char	*tmp[4];
	t_arg	*tok;
	char	**mirror;

	i = 0;
	ft_bzero(tmp, sizeof(char *) * 4);
	mirror = cmd->args;
	(void)mirror;
	while (cmd->args[i])
	{
		tmp[0] = cmd->args[i];
		if (msh_is_token(cmd->args[i]))
		{
			tok = msh_get_token_value(cmd, cmd->args[i]);
			msh_token_mutations(tok);
			ft_strdel(&cmd->args[i]);
			if (!tmp[0])
			{
				i++;
				continue;
			}
			if (!tok->has_prefix && !tok->is_prefix)
			{
				cmd->args[i] = ft_strdup(tok->value);
				i++;
				continue;
			}
			if (tok->has_prefix)
			{
				if (msh_is_token(cmd->args[i - 1]))
					tmp[1] = msh_get_token_value(cmd, cmd->args[i - 1])->value;
				else
					tmp[1] = cmd->args[i - 1];
				tmp[2] = ft_strjoin(tmp[1], tok->value);
				ft_strdel(&cmd->args[i - 1]);
			}
			if (tok->is_prefix)
			{
				if (!tmp[2])
					tmp[2] = ft_strdup(tok->value);
				msh_recursion_eval(i + 1, cmd, &tmp[2]);
			}
			else
				cmd->args[i] = tmp[2];
			msh_replace_null_arg(cmd);
			ft_bzero(tmp, sizeof(char *) * 4);
		}
		else
			i++;
	}
}

int msh_make_path_relative(t_command *cmd)
{
	int res;
	char *tmp;

	res = 0;
	tmp = NULL;
	tmp = msh_get_path(cmd->args[0], g_info.env);
	if (!tmp && msh_get_env_by_key(g_info.env, "PATH"))
	{
		msh_error_bash("command not found", cmd->args[0], 127);
		res = 1;
	}
	else if (!tmp && !msh_get_env_by_key(g_info.env, "PATH"))
		return (msh_error_bash("No such file or directory", cmd->args[0], 127));
	else
	{
		ft_swap_strs(&cmd->args[0], &tmp);
		ft_strdel(&tmp);
	}
	return (res);
}

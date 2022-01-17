/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:33 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/16 19:49:34 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

int msh_provider(char first, int *i, char *str, char *set)
{
	if (first != 0)
		return (first);
	else if (i[0] != (int)ft_strlen(str) && first == 0)
		return (msh_is_odd_quote(first, str + i[0], set));
	else
		return (0);
}

int	msh_is_odd_quote(char first, char *str, char *set)
{
	int 		i[2];

	ft_bzero(i, sizeof(int) * 2);
	while (str[i[0]])
	{
		i[1] = 0;
		while (first == 0 && set[i[1]])
		{
			if ((unsigned char)str[i[0]] - (unsigned char)set[i[1]] == 0)
			{
				first = str[i[0]++];
				break;
			}
			i[1]++;
		}
		if (first != 0
			&& (unsigned char)str[i[0]] - (unsigned char)first == 0)
		{
			first = 0;
			i[0]++;
			break ;
		}
		i[0]++;
	}
	return (msh_provider(first, i, str, set));
}

char	*msh_strncat(char *new, char *dyn_buff)
{
	int	line_l;
	int	buff_l;

	buff_l = ft_strlen(dyn_buff);
	line_l = ft_strlen(new);
	dyn_buff = ft_realloc(dyn_buff, sizeof(char) * (buff_l + line_l + 1));
	ft_strncat(dyn_buff, new, buff_l + line_l + 1);
	return (dyn_buff);
}

void	msh_is_close_odd_quote(char **line, char *buf_sd, char *c)
{
	int	buf_len;

	buf_len = ft_strlen(buf_sd);
	*line = msh_strncat(*line, buf_sd);
	*c = msh_is_odd_quote(*c, *line + buf_len, "'\"");
}

int	msh_unclosed_quotes(char **line, char *buf_sd, char c)
{
	char	*quote_type;
	
	if (!c)
		c = msh_is_odd_quote(0, *line, "'\"");
	else
		msh_is_close_odd_quote(line, buf_sd, &c);
	if (c)
	{
		if (QUOTES_ADD_REGIME)
		{
			if (c == '\'')
				quote_type = "quote> ";
			else
				quote_type = "dquote> ";
			buf_sd = *line;
			msh_readline(quote_type, line);
			msh_unclosed_quotes(line, buf_sd, c);
		}
		else
			return (msh_unexpected_token_error("unclosed quote", 15));
	}
	return (0);
}

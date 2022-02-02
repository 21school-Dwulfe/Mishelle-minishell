/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:44:14 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/28 20:44:47 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_clumpted_address(char *str, int index)
{
	char	*p;
	char	*p2;
	char	*ptr;
	int		i;

	i = index + 1;
	p = NULL;
	p2 = NULL;
	if (str[index] == '\0' || str[index + 1] == '\0'
		|| str[index + 1] == '<' || str[index + 1] == '>')
		return (0);
	while (str[i] == ' ')
		i++;
	if (index + 1 != i)
		return (0);
	ptr = msh_get_next_word(str, index, " ");
	p = ft_strchr(ptr, '<');
	p2 = ft_strchr(ptr, '>');
	if (p)
		return (msh_unexpected_token_error(p, 1));
	if (p2)
		return (msh_unexpected_token_error(p2, 1));
	else
		return (0);
}

void	msh_nevlezlo(char *str, int *l, int *i)
{
	while (str[l[0]] == str[*i] && (l[0] - *i) + 1 < 3)
		l[0]++;
	while (str[l[0]] == ' ')
		l[0]++;
}

int	msh_validation_redirs(char *str, int *i)
{
	int		l[5];
	char	*ptr;

	ptr = NULL;
	ft_bzero(l, sizeof(int) * 5);
	l[0] = *i;
	msh_nevlezlo(str, l, i);
	l[4] = msh_clumpted_address(str, l[0]);
	if (l[4])
		return (l[4]);
	if (str[l[0]] == '<' && str[l[0] + 1] == '>')
		return (msh_unexpected_token_error(&str[l[0]], 2));
	ptr = ft_strchr("|;<>", str[l[0]]);
	if (ptr)
		l[2] = *ptr;
	if (str[l[0]] == '\0')
		return (msh_unexpected_token_error("newline", 7));
	if (!(ft_abs(l[2] - str[*i]) == 2))
		l[3] = 1;
	l[1] = l[0];
	while (str[l[1]] == l[2] && l[1] + l[3] - l[0] < 3)
		l[1]++;
	if (l[2] && l[2] != 'n')
		return (msh_unexpected_token_error(str + l[0], l[1] - l[0]));
	return (0);
}

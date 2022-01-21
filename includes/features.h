/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:56:05 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 19:56:06 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURES_H
# define FEATURES_H

int			msh_is_odd_quote(char first, char *str, char *set);
void		msh_is_close_odd_quote(char **line, char *buf_sd, char *c);
int			msh_unclosed_quotes(char **line, char *buf_sd, char c);
void		msh_readline(char *prefix, char **dest);

#endif
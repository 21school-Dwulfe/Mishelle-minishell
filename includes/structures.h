#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "libs.h"

typedef struct	s_token
{
	char	*cmd;
	char	*flags;
}				t_token;

typedef struct	s_info
{
	char		is_odd_single_quatations;
	char		is_odd_double_quatations;
	char		odd_quotations;
	t_token		*tokens;

}				t_info;

t_info	g_info;

#endif
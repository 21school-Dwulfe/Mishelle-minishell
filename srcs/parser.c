#include "../includes/main.h"

//parse string until occurs special or stop signs( ; | & > >> < << <& <<& \n)
// validation operators order
// validation cmd names
// validation cmd args


int	msh_check_special_signs(char *str, int i)
{
	int	j;
	int k;

	j = i;
	k = i;
	while (str[j] || str[k])
	{
		if (str[j])
		{

		}
	}
}

char **msh_split(char *str, char *c)
{
	int		length;
	char	**result;

	length = 0;
	while ()
	{


	}
}

int	msh_is_quatation(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 27 || str[i] == 22)
			return (1);
		i++;
	}
	return (0);
}

t_s_command *msh_parse(char *str)
{
	int		len;
	int		quatation;
	int		i;
	char	*cmds;
	t_s_command *token;

	i = 0;
	quatation = msh_is_quatation(str);
	if (quatation)
	 	cmds = msh_split_quatation(str);
	else
		cmds = ft_split(str, " ");
	return (token);
}
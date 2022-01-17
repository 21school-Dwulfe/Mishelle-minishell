#include "../../includes/main.h"
#include "../../includes/main.h"

char	*msh_token_wild_card(char *str, int *i)
{
	struct dirent	*ent;
	DIR				*dir;
	char			*tmp;
	char			*result;
  
	result = NULL;
	dir = opendir(msh_get_env_by_key(g_info.env, "PWD"));
	if (dir != NULL)
	{
		while (1)
		{
			ent = readdir(dir);
			if (!ent)
				break ;
			if (*ent->d_name != '.')
			{
				if (!result)
					result = ft_strdup(ent->d_name);
				else
				{
					tmp = result;
					result = ft_strjoin(tmp, *ent->d_name);
					ft_strdel(&tmp);
				}
			}
		}
		closedir(dir);
	}
	return (result);
}
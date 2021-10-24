char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)s;
	while (ptr[i] != c)
	{
		if (ptr[i] == '\0')
			return ((void *)0);
		i++;
	}
	return (&ptr[i]);
}

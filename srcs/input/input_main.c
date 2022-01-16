
void	msh_stdin_regime(void)
{
	char	*line;
	
	line = NULL;
	while (1)
	{
		msh_readline("\001\e[32m\002MISHELLE >>> \001\e[37m\002", &line);
		if (msh_validate_line(line))
			continue ;
		add_history(line);
		if (!msh_unclosed_quotes(&line, NULL, 0))
			msh_cmd(&line);
		ft_strdel(&line);
		msh_struct_clear();
		msh_init_global_cmd();
	}
}
